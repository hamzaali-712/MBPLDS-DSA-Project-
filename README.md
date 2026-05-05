# 🛡️ MBPLDS – Memory-Based Password Leak Detection System

![C++](https://img.shields.io/badge/C++-17-blue.svg?style=for-the-badge&logo=c%2B%2B)
![Python](https://img.shields.io/badge/Python-3.9%2B-yellow.svg?style=for-the-badge&logo=python)
![Streamlit](https://img.shields.io/badge/Streamlit-FF4B4B.svg?style=for-the-badge&logo=Streamlit)
![Groq](https://img.shields.io/badge/Groq-AI-f55036.svg?style=for-the-badge&logo=ai)

## 📌 Project Overview
The **Memory-Based Password Leak Detection System (MBPLDS)** is a high-performance cybersecurity application designed to intelligently manage users, evaluate password strength, prevent password reuse, and identify high-risk accounts in real-time. 

Developed by **HAMZA ALI**, this project bridges a **lightning-fast C++ Data Structures backend** with a **modern Streamlit web frontend**, utilizing the Groq AI API (`llama-3.1-8b-instant`) to generate personalized, actionable security reports.

## ✨ Core Features & Data Structures

Our engine ensures mission-critical operations run in $O(1)$ or $O(\log N)$ time complexity by leveraging custom-built Data Structures:

- **User Directory (Binary Search Tree)**: Efficient $O(\log N)$ user insertion, lookup, and management.
- **Weak Password Detection (Trie / Prefix Tree)**: Instantly flags common dictionary passwords and predictable patterns character-by-character in $O(L)$ time.
- **Leak Detection (Hash Table)**: Lightning-fast $O(1)$ lookup against a database of known compromised SHA-256 password hashes.
- **Password History & Undo (Stack)**: Retains historical hashes to prevent users from reusing recent passwords. Allows Admins to "undo" a password change in $O(1)$ time.
- **Live Risk Monitoring (Max-Heap Priority Queue)**: Automatically calculates user risk scores (based on entropy, leaks, and weakness) and bubbles the most vulnerable accounts to the top for Admin review.
- **Mathematical Entropy Engine**: Calculates Brute-Force resistance using combination mathematics ($Pool Size^{Length}$) to estimate exact GPU cracking times.

## 📂 Architecture & Directory Structure

```text
MBPLDS-DSA-Project-/
├── src/                            # C++ Source Code
│   ├── main.cpp                    # Backend Entry point
│   ├── core/                       # User and Password Entities
│   ├── datastructures/             # Custom BST, Trie, Max-Heap, Hash Table
│   ├── engine/                     # UserManager, HashUtils, PasswordEngine
│   ├── database/                   # DatabaseManager & Schema Mock
│   └── ui/                         # Command Line Interface (CLI)
├── data/                           # Mock datasets (leaks, weak passwords, JSON)
├── docs/                           # Architecture, Class, and Sequence Diagrams
├── tests/                          # Unit testing directory
├── app.py                          # Streamlit Web Frontend
├── build.sh                        # Bash script for dynamic compilation
├── requirements.txt                # Python dependencies
└── CMakeLists.txt                  # C++ Build Configuration
```

## 🚀 Getting Started

You can run MBPLDS via the **Admin CLI (C++)** or the **Web GUI (Python/Streamlit)**.

### Prerequisites
- **C++17 Compiler** (GCC/MinGW, Clang, or MSVC)
- **Python 3.9+**
- **CMake** (v3.10 or higher) (Optional, for manual builds)

### 🌐 1. Streamlit AI Web GUI (Recommended)

Experience the premium, responsive dashboard complete with dynamic charts and Groq AI reports.

1. **Install Python dependencies:**
   ```bash
   pip install -r requirements.txt
   ```
2. **Set up your environment:**
   Create a `.env` file from `.env.example` and add your Groq API key (to enable the `llama-3.1-8b-instant` model):
   ```env
   GROQ_API_KEY=your_groq_api_key_here
   ```
3. **Launch the App:**
   ```bash
   streamlit run app.py
   ```
   *Note: The app will automatically run `build.sh` to compile the C++ backend if it doesn't already exist.*

### 💻 2. C++ Admin CLI

Run the raw backend interface for managing users and viewing the Priority Queue Risk Heap.

1. **Build the executable:**
   ```bash
   bash build.sh
   ```
   *(Alternatively, use CMake `cmake . && cmake --build .`)*
2. **Run the CLI:**
   ```bash
   ./mbplds       # On Linux/Mac
   ./mbplds.exe   # On Windows
   ```
3. **Login:** Use the default mock credentials (`Username: MBPLDS`, `Password: Admin@123`).

## ☁️ Deploying to Streamlit Cloud

This project is optimized for deployment on the Streamlit Community Cloud.
1. Push this repository to GitHub.
2. Link the repository to your Streamlit Cloud account.
3. Add your `GROQ_API_KEY` to the **Secrets** in Streamlit Advanced Settings.
4. Deploy! The cloud environment uses `packages.txt` to install `g++` and executes `build.sh` to compile the C++ engine before booting the Python UI.

---
<div align="center">
  <i>Developed for the Data Structures & System Design Semester Project.</i>
</div>
