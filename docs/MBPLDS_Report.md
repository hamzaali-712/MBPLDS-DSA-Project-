# MBPLDS – Memory-Based Password Leak Detection System
## Complete System Design & Project Report

---

### 1. Project Overview & Motivation
**Problem:** 
Modern security systems struggle with users choosing weak passwords, reusing old ones, or using credentials exposed in data breaches. Traditional systems often fail to evaluate these risks in real-time or lack efficient data structures to process mathematical entropy and substring patterns instantly.

**Our Solution (MBPLDS):** 
Developed for the Data Structures & System Design Semester Project by a dedicated team at **COMSATS University Islamabad, Wah Campus**, MBPLDS solves this problem using a hybrid architecture. It combines a lightning-fast C++ Data Structures Engine with a premium, responsive Python Streamlit Dashboard. Furthermore, it integrates the **Groq AI LLM** (`llama-3.1-8b-instant`) to provide users with personalized, professional security reports.

---

### 2. Team & Responsibilities

| Team Member | Role | Key Contributions |
|---|---|---|
| **Hamza Ali** | Team Lead | AI Integration, Streamlit Deployment, Remaining Backend Engine & Project Architecture. |
| **Adnan Shah** | Member | UI/UX Design, Glassmorphism CSS, and Module Testing. |
| **Farukh Mumtaz** | Member | Cryptographic Hashing Implementation, Documentation, System Testing & Bug Fixing. |

---

### 3. System Architecture
The system operates across a multi-language pipeline:
1. **Presentation Layer (Python/Streamlit):** Captures user input securely. Displays metrics, dynamic Altair risk graphs, and the AI Security Report.
2. **Execution Layer (Subprocess):** The Python app dynamically compiles and executes the C++ binary (`mbplds.exe`), passing the password via CLI flags.
3. **Business Logic Layer (C++):** `PasswordEngine` evaluates mathematical entropy ($Pool Size^{Length}$). `HashUtils` computes a true bitwise SHA-256 hash.
4. **Data Structure Layer (C++):** Passwords are run through the `WeakPasswordTrie` and the `LeakHashTable`.
5. **Persistence Layer (Text/SQL Mock):** Real-time loading of datasets from `data/weak_passwords.txt` and `data/leaked_hashes.txt`.

---

### 4. Core Data Structures Justification

| DATA STRUCTURE | WHERE USED | WHY CHOSEN |
|---|---|---|
| **Binary Search Tree (BST)** | User Directory | $O(\log N)$ search, insert, and delete. Perfect for structured user management without heavy overhead. |
| **Hash Table** (`unordered_set`) | Leak Detection | $O(1)$ average lookup. Allows instant matching of a 64-character SHA-256 hash against millions of known breaches. |
| **Trie (Prefix Tree)** | Weak Pattern Matching | Modified for **case-insensitive substring pattern matching** in $O(L^2)$ time. Instantly detects if a password *contains* common sequences (e.g., "123"). |
| **Max-Heap** (`priority_queue`) | Risk Prioritization | $O(1)$ get-max. Used by the CLI admin panel to instantly bubble the highest-risk users to the top. |
| **Stack** | Password History | LIFO structure naturally models password history, preventing users from reusing their last N passwords. |

---

### 5. Advanced Features & Algorithms

#### A. True Cryptographic SHA-256 Hashing
Initially, the project used an academic mock hash. **Farukh Mumtaz** upgraded this to a true bitwise SHA-256 implementation involving chunk processing, 64-round compression (`CH`, `MAJ`, `SIG0`, etc.), and proper bit padding. This guarantees the system can accurately verify passwords against real-world breach databases.

#### B. Substring Weak Pattern Detection
Standard Tries only allow exact matching. **Hamza Ali** overhauled the Trie search algorithm to check every possible substring of the input against the Trie paths. If a user enters `Hamza@123`, the system successfully extracts and flags `123` as a known weak pattern.

#### C. AI Integration via Groq
The C++ backend outputs a raw JSON string containing entropy, hash, leak status, and crack times. **Hamza Ali** integrated the `Groq` API into the Python frontend. The JSON data is securely sent to the `llama-3.1-8b-instant` model alongside a custom prompt, generating a 3-paragraph professional cybersecurity report with personalized tips.

---

### 6. JSON Integration Format
The communication between C++ and Python relies on a strict JSON schema printed to `stdout`:
```json
{
  "password": "Hamza@123",
  "hash": "ee584d262057bd426087d656431a6a30f42ff94f36ebe6f02ade6ff835f2aaf4",
  "isWeak": true,
  "isLeaked": true,
  "entropy": 58.9913,
  "crackTimeSeconds": 57299500.00
}
```
*The Streamlit App (UI/UX by **Adnan Shah**) parses this JSON safely, preventing crashes if the binary execution fails.*

---

### 7. Deployment Strategy
The project is completely configured for **Streamlit Community Cloud** deployment.
- **`packages.txt`:** Instructs the Debian cloud server to `apt-get install g++`.
- **`build.sh`:** A bash script that compiles the 8+ C++ source files into a single binary.
- **Dynamic Compilation:** `app.py` checks if the binary exists. If not, it executes `build.sh` automatically before loading the UI. This ensures cross-platform compatibility (Windows `.exe` vs Linux ELF).
- **Secrets Management:** The Groq API key is hidden securely in the Cloud Secrets to prevent public exposure on GitHub.
