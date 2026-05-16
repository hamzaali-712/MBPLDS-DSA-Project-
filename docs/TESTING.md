# Comprehensive Testing Strategy & Results

This document outlines the rigorous testing methodologies applied across all layers of the MBPLDS application.

---

## 1. UI/UX Validation & Module Testing
**Lead Tester: Adnan Shah**

*Focus: Ensuring the Streamlit web dashboard renders perfectly, components respond cleanly, and individual C++ data structures perform correctly in isolation.*

| TEST CASE | INPUT | EXPECTED OUTPUT | STATUS |
|---|---|---|---|
| Dashboard Load | Run `streamlit run app.py` | UI loads seamlessly with Dark mode | ✅ PASS |
| Empty Password | Click Analyze with no input | Streamlit warning: "Please enter a password first." | ✅ PASS |
| C++ Integration | Valid Password string | Dashboard successfully parses JSON output | ✅ PASS |
| Risk UI Coloring | Weak/Leaked password | Card turns Red (Critical 🔴) | ✅ PASS |
| Risk UI Coloring | Strong password | Card turns Green (Safe 🟢) | ✅ PASS |
| Altair Graphs | Entropy score 58.99 | Graph dynamic bar updates proportionally | ✅ PASS |
| UserBST Insertion | 1,000 dummy users | $O(\log N)$ fast insertion with no memory leaks | ✅ PASS |

---

## 2. System Testing, Hashing Verification & Bug Fixing
**Lead Tester: Farukh Mumtaz**

*Focus: Guaranteeing the integrity of the real SHA-256 implementation, verifying the dataset loading mechanics, and resolving substring pattern detection bugs.*

| TEST CASE | INPUT | EXPECTED OUTPUT | STATUS |
|---|---|---|---|
| Real SHA-256 Hash | `"password"` | `5e884898da28047151d0e56f8dc6...` (Bitwise match) | ✅ PASS (Bug Fixed) |
| Data Breach Check | `"password"` | `LeakHashTable` matches hash, `isLeaked = true` | ✅ PASS |
| Safe Password Check | `"Str0ng#2026"` | Hash not in `leaked_hashes.txt`, `isLeaked = false` | ✅ PASS |
| Exact Weak Match | `"123456"` | `WeakPasswordTrie` detects it, `isWeak = true` | ✅ PASS |
| Case-Insensitive | `"ADMIN"` | Lowercased internally, matches "admin" | ✅ PASS |
| **Substring Match** | `"Hamza@123"` | Detects "123" inside string, `isWeak = true` | ✅ PASS (Bug Fixed) |
| Missing DB Files | Rename `data/` to `data_old/` | Fallbacks activate without crashing engine | ✅ PASS |

---

## 3. AI Integration & Deployment Testing
**Lead Tester: Hamza Ali (Team Lead)**

*Focus: Streamlit Community Cloud deployment configuration, automated build pipelines, and Groq LLM API robustness.*

| TEST CASE | INPUT | EXPECTED OUTPUT | STATUS |
|---|---|---|---|
| Dynamic C++ Compile | Windows/Linux OS | `build.sh` executed if `.exe`/bin missing | ✅ PASS |
| Cloud Packages | `packages.txt` with `g++` | Streamlit Cloud installs C++ compiler | ✅ PASS |
| API Key Missing | Click "Check AI Report" | UI displays info box to configure `.env` | ✅ PASS |
| Groq Prompt Gen | Valid JSON metrics | LLM generates exactly 3 paragraphs with 2 tips | ✅ PASS |
| Legacy Model Deprec. | `llama3-8b-8192` decommissioned | Switched to `llama-3.1-8b-instant` | ✅ PASS (Bug Fixed) |
| Cloud Deployment | Push to GitHub `main` | Dashboard goes live globally within 2 minutes | ✅ PASS |
