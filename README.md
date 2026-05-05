# MBPLDS – Memory-Based Password Leak Detection System

## 📌 Project Overview
The **Memory-Based Password Leak Detection System (MBPLDS)** is a high-performance, C++ based cybersecurity application. It intelligently manages users and passwords while detecting leaks, preventing password reuse, and identifying high-risk accounts in real-time. 

This project heavily utilizes advanced **Data Structures** (Binary Search Trees, Tries, Max-Heaps, Hash Tables, and Stacks) to ensure operations like leak detection and risk evaluation happen in $O(1)$ or $O(\log N)$ time complexity.

## ✨ Features & Data Structures Used
- **User Directory (Binary Search Tree)**: $O(\log N)$ user insertion and lookup.
- **Weak Password Detection (Trie / Prefix Tree)**: Instantly flags common passwords character-by-character.
- **Leak Detection (Hash Table)**: $O(1)$ lookup against a database of known compromised SHA-256 password hashes.
- **Password History & Undo (Stack)**: Prevents users from reusing recent passwords and allows Admins to "undo" a password change in $O(1)$ time.
- **Live Risk Monitoring (Max-Heap Priority Queue)**: Automatically calculates user risk scores and bubbles the most vulnerable accounts to the top for Admin review.
- **Mock MySQL Persistence**: Automatically generates SQL `INSERT`, `UPDATE`, and `DELETE` queries to simulate database persistence.

## 📂 Directory Structure
```text
MBPLDS/
├── src/
│   ├── main.cpp                    # Entry point
│   ├── core/                       # User and Password Entities
│   ├── datastructures/             # Custom BST, Trie, Max-Heap, Hash Table
│   ├── engine/                     # UserManager, HashUtils, PasswordEngine
│   ├── database/                   # DatabaseManager & Schema
│   └── ui/                         # Command Line Interface (CLI)
├── data/                           # Mock datasets (leaks, weak passwords, JSON)
├── docs/                           # Architecture, Class, and Sequence Diagrams
├── tests/                          # Unit testing directory
└── CMakeLists.txt                  # Build Configuration
```

## 🚀 How to Build and Run

### Prerequisites
- **C++17 Compiler** (GCC/MinGW, Clang, or MSVC)
- **CMake** (v3.10 or higher)

### Build Instructions
1. Open your terminal in the project root directory.
2. Generate the build files using CMake:
   ```bash
   cmake .
   ```
3. Build the executable:
   ```bash
   cmake --build .
   ```
   *(Alternatively, compile manually with g++):*
   ```bash
   g++ -I src src/main.cpp src/core/User.cpp src/core/PasswordRecord.cpp src/engine/UserManager.cpp src/engine/HashUtils.cpp src/engine/PasswordEngine.cpp src/database/DatabaseManager.cpp src/ui/CLI.cpp -o mbplds
   ```
4. Run the application:
   ```bash
   ./mbplds    # On Linux/Mac
   mbplds.exe  # On Windows
   ```

## 💻 Usage (Admin CLI)
Upon running the application without arguments, you will be greeted by the **MBPLDS Admin Security Console**.
1. Select **Login as Admin**.
2. Use the default mock credentials:
   - **Username**: `MBPLDS`
   - **Password**: `Admin@123`
3. From the Admin Dashboard, you can add users, update passwords, view the live Risk Max-Heap, and trigger the "Undo" stack mechanism!

## 🌐 Streamlit AI Web GUI
We have built a premium, modern Web GUI using Python's **Streamlit** that integrates directly with our C++ backend, utilizing the **Groq AI** LLM for personalized security reports!

### Prerequisites for Web GUI
- **Python 3.9+**
- **Groq API Key** (for the AI Report Generator)

### How to Run Locally
1. Compile the C++ Backend (if you haven't already):
   ```bash
   bash build.sh
   # Or run the g++ command from above manually
   ```
2. Install Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Create a `.env` file from `.env.example` and add your API key:
   ```env
   GROQ_API_KEY=your_groq_api_key_here
   ```
4. Launch the Streamlit App:
   ```bash
   streamlit run app.py
   ```

### Deploying to Streamlit Cloud
This project is fully configured to deploy on Streamlit Community Cloud!
1. Push the repository to GitHub.
2. Link the repository to your Streamlit Cloud account.
3. In Streamlit Cloud Advanced Settings, add your `GROQ_API_KEY` to the **Secrets**.
4. Deploy! The cloud will automatically read `packages.txt` to install `g++` and execute `build.sh` to compile the C++ backend dynamically before the Python app boots!

---
*Developed for the Data Structures & System Design Semester Project.*
