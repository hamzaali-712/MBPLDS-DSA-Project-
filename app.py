import streamlit as st
import subprocess
import json
import os
import platform
import pandas as pd
import altair as alt
from groq import Groq

# Page Config
st.set_page_config(page_title="MBPLDS Dashboard", page_icon="🛡️", layout="wide")

# Custom CSS for Glassmorphism & Aesthetics
st.markdown("""
<style>
    .stApp {
        background-color: #0E1117;
        color: #FAFAFA;
    }
    .metric-card {
        background: rgba(255, 255, 255, 0.05);
        backdrop-filter: blur(10px);
        border: 1px solid rgba(255, 255, 255, 0.1);
        border-radius: 15px;
        padding: 20px;
        text-align: center;
        margin: 10px;
    }
    .metric-value {
        font-size: 2rem;
        font-weight: bold;
        color: #00ffcc;
    }
    .warning-text { color: #ff4b4b; font-weight: bold; }
    .safe-text { color: #00ffcc; font-weight: bold; }
</style>
""", unsafe_allow_html=True)

st.title("🛡️ Memory-Based Password Leak Detection System")
st.markdown("Test your password strength against our custom C++ Data Structures Backend and generate a personalized AI Security Report.")

with st.expander("ℹ️ How This System Works (C++ Data Structures)"):
    st.markdown("""
    This system is powered by a high-performance **C++ Backend** utilizing advanced Data Structures:
    - **WeakPasswordTrie (Prefix Tree):** Instantly detects if your password contains common weak patterns in $O(L)$ time.
    - **LeakHashTable (Hash Map):** Checks your SHA-256 hashed password against known data breaches in $O(1)$ time.
    - **Mathematical Entropy Engine:** Calculates Brute-Force resistance using combination mathematics ($Pool\\ Size^{Length}$) to estimate exact GPU cracking times.
    - **UserBST & RiskMaxHeap:** Actively manages users and monitors high-risk vulnerabilities dynamically.
    """)

password_input = st.text_input("Enter Password to Analyze:", type="password")

col1, col2 = st.columns([1, 1])
with col1:
    analyze_btn = st.button("🔍 Analyze Password", use_container_width=True)
with col2:
    report_btn = st.button("📄 Check AI Security Report", use_container_width=True)

if analyze_btn or report_btn:
    if not password_input:
        st.warning("Please enter a password first.")
    else:
        # 1. Call C++ Backend
        try:
            # Determine executable name based on OS
            exe_name = "./mbplds.exe" if platform.system() == "Windows" else "./mbplds"
            
            # Compile dynamically if it doesn't exist (useful for Streamlit Cloud)
            if not os.path.exists(exe_name):
                with st.spinner("Compiling C++ Backend..."):
                    subprocess.run(["bash", "build.sh"], check=True)
                    exe_name = "./mbplds"
            
            result = subprocess.run([exe_name, "--analyze", password_input], capture_output=True, text=True)
            
            try:
                data = json.loads(result.stdout.strip())
            except json.JSONDecodeError:
                st.error("Error parsing backend output. Ensure the C++ executable is compiled and outputting raw JSON.")
                st.code(result.stdout)
                st.stop()

            st.subheader("C++ Backend Engine Results")
            
            # Mathematical Calculations
            attempts = 2 ** data['entropy']
            
            # Determine Risk Level
            if data['isLeaked'] or data['isWeak']:
                risk_level = "CRITICAL 🔴"
                risk_color = "#ff4b4b"
            elif data['entropy'] < 40:
                risk_level = "HIGH RISK 🟠"
                risk_color = "#ff9c33"
            elif data['entropy'] < 60:
                risk_level = "WARNING 🟡"
                risk_color = "#f2ff00"
            else:
                risk_level = "SAFE 🟢"
                risk_color = "#00ffcc"
            
            st.markdown(f"""
            <div class="metric-card" style="border: 2px solid {risk_color};">
                <h3>Overall Security Status</h3>
                <h1 style="color: {risk_color};">{risk_level}</h1>
                <p style="font-size: 1.2rem;">Total Brute-Force Attempts Required: <b>{attempts:,.0f} combinations</b></p>
            </div>
            """, unsafe_allow_html=True)
            
            # Display Metrics
            colA, colB, colC, colD = st.columns(4)
            with colA:
                st.markdown(f"""
                <div class="metric-card">
                    <div>Hash (SHA-256)</div>
                    <div class="metric-value" style="font-size: 1rem;">{data['hash'][:12]}...</div>
                </div>
                """, unsafe_allow_html=True)
            with colB:
                st.markdown(f"""
                <div class="metric-card">
                    <div>Entropy Score</div>
                    <div class="metric-value">{data['entropy']:.2f}</div>
                </div>
                """, unsafe_allow_html=True)
            with colC:
                weak_html = '<span class="warning-text">YES</span>' if data['isWeak'] else '<span class="safe-text">NO</span>'
                st.markdown(f"""
                <div class="metric-card">
                    <div>Weak Pattern Detected</div>
                    <div class="metric-value" style="font-size: 1.5rem;">{weak_html}</div>
                </div>
                """, unsafe_allow_html=True)
            with colD:
                leak_html = '<span class="warning-text">YES</span>' if data['isLeaked'] else '<span class="safe-text">NO</span>'
                st.markdown(f"""
                <div class="metric-card">
                    <div>Data Breach Leaked</div>
                    <div class="metric-value" style="font-size: 1.5rem;">{leak_html}</div>
                </div>
                """, unsafe_allow_html=True)
                
            st.markdown(f"""
            <div class="metric-card">
                <h3>Estimated Time to Crack (Brute Force at 10B/sec)</h3>
                <h1 class="metric-value" style="color: {'#ff4b4b' if data['crackTimeSeconds'] < 3600 else '#00ffcc'}">
                    {data['crackTimeSeconds']:,.2f} seconds
                </h1>
            </div>
            """, unsafe_allow_html=True)

            # Security Spectrum Graph (Altair)
            st.subheader("📊 Password Security Spectrum")
            graph_data = pd.DataFrame({
                "Category": ["Your Password", "Minimum Safe Benchmark", "Military Grade"],
                "Entropy (Bits)": [data['entropy'], 60, 128]
            })
            
            chart = alt.Chart(graph_data).mark_bar().encode(
                x=alt.X('Entropy (Bits):Q', title="Entropy Score (Higher is Better)"),
                y=alt.Y('Category:N', sort="-x", title=""),
                color=alt.condition(
                    alt.datum.Category == 'Your Password',
                    alt.value(risk_color),     # Color matches the risk level
                    alt.value('#3b4252')       # Color for benchmarks
                ),
                tooltip=['Category', 'Entropy (Bits)']
            ).properties(height=200).interactive()
            
            st.altair_chart(chart, use_container_width=True)

            # 2. AI Report Generator (Only if button is clicked)
            if report_btn:
                st.subheader("🤖 AI Security Report")
                api_key = os.getenv("GROQ_API_KEY")
                if not api_key:
                    st.info("Set your GROQ_API_KEY in `.env` or Streamlit Secrets to automatically generate the AI Security Report.")
                else:
                    with st.spinner("Analyzing with Groq AI..."):
                        try:
                            client = Groq(api_key=api_key)
                            prompt = f"""
                            You are a Senior Cybersecurity Analyst. Analyze this password detection data from our C++ Engine:
                            - Password length: {len(data['password'])}
                            - Entropy: {data['entropy']:.2f}
                            - Is Weak Pattern: {data['isWeak']}
                            - Is Found in Leaks: {data['isLeaked']}
                            - Brute Force Crack Time: {data['crackTimeSeconds']:.2f} seconds
                            
                            Write a concise, professional 3-paragraph report for a system developed by HAMZA ALI. 
                            1. Evaluate the risk based on the data.
                            2. Explain what the crack time means practically to the user.
                            3. Give exactly 2 actionable tips using symbols or patterns to make it exponentially harder to crack. Do not repeat the actual password.
                            """
                            
                            response = client.chat.completions.create(
                                messages=[{"role": "user", "content": prompt}],
                                model="llama-3.1-8b-instant"
                            )
                            st.success("Report Generated Successfully!")
                            st.write(response.choices[0].message.content)
                        except Exception as e:
                            st.error(f"AI Generation Error: {e}")
                        
        except Exception as e:
            st.error(f"Failed to execute C++ backend. Error: {e}")

# Footer Details
st.markdown("---")
st.markdown("""
<div style="text-align: center; color: #888; padding-top: 20px;">
    <b>DSA PROJECT 4TH SEMESTER</b><br>
    COMSATS UNIVERSITY ISLAMABAD, WAH CAMPUS<br>
    <i>TEAM LEAD: HAMZA ALI | MEMBERS: ADNAN SHAH AND FARUKH MUMTAZ</i>
</div>
""", unsafe_allow_html=True)
