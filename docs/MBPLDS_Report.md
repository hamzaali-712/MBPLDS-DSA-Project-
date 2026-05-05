# MBPLDS – Memory-Based Password Leak Detection System
## Complete System Design & Implementation Plan

### 1. Project Overview
**Problem Being Solved:**
Modern security systems struggle with users choosing weak passwords, reusing old ones, or using credentials that have already been exposed in data breaches. Traditional systems often fail to monitor account risk in real-time or lack efficient data structures to handle millions of checks without lag.

**How the System Works (Step-by-Step):**
1. **Request Reception:** A user requests to register or change their password. The request is placed in a processing Queue.
2. **Security Validation:** 
   - The system checks the password against a Hash Table of known weak passwords (e.g., "admin", "123456").
   - It hashes the password and checks a massive Hash Table of known leaked passwords (simulated leak database).
3. **History Verification:** If valid, the system traverses the user's Password History Stack to ensure the password hasn't been used recently.
4. **State Update & Undo:** The old password is pushed to the History Stack (allowing an "Undo" operation if needed), and the new password is set.
5. **Risk Assessment:** A risk score is calculated based on the user's actions (e.g., attempt to use a leaked password adds +50 to risk). 
6. **Prioritization:** The user is updated in a Max-Heap (Priority Queue). The admin dashboard always displays the highest-risk users at the root for immediate action.
7. **Persistence:** All state changes are asynchronously written to a MySQL database.

---

### 2. System Architecture
**Modules & Data Flow:**
- **API / Request Handler Module:** Uses a Queue to manage incoming user requests. Prevents system overload during traffic spikes.
- **User Management Module:** Maintains an AVL Tree (Binary Search Tree) of all users. Handles fast lookups, registrations, and deletions.
- **Security & Password Module:** Manages the Hash Tables for leak/weak detection and the Stacks for password history.
- **Risk Assessment Engine:** Maintains the Max-Heap. Continuously re-evaluates risk scores when users interact with the system.
- **DatabaseManager:** Abstract interface to MySQL. On startup, it populates the memory data structures. During runtime, it persists changes.

**Interaction:**
`User Request -> Request Queue -> Dispatcher -> Security Module -> User Module -> Risk Engine -> DatabaseManager`

---

### 3. Major Classes & Responsibilities

#### `User`
- **Properties:** `userID`, `username`, `passwordHash`, `riskScore`.
- **Responsibilities:** Holds user state.
- **Relationships:** Contains a `PasswordStack` for history.

#### `PasswordStack` (Custom Stack)
- **Properties:** `Node* top`, `currentSize`, `maxSize` (e.g., 5).
- **Responsibilities:** Manages the last N passwords for the user. Enables `undo()`.

#### `UserManager`
- **Properties:** `AVLTree<User> userTree`.
- **Responsibilities:** Adds, deletes, and searches users efficiently. Enforces unique usernames.

#### `SecurityManager`
- **Properties:** `HashTable<string, bool> leakedHashes`, `HashTable<string, bool> weakPasswords`.
- **Responsibilities:** Hashes raw passwords, detects leaks in O(1) time, checks for weak patterns.

#### `RiskManager`
- **Properties:** `MaxHeap<User*> riskQueue`.
- **Responsibilities:** Recalculates risk based on predefined rules. Bubbles high-risk users to the top of the heap.

#### `DatabaseManager`
- **Responsibilities:** Executes SQL queries (SELECT, INSERT, UPDATE, DELETE). Translates database rows into C++ Objects.

---

### 4. Core Algorithms & Time Complexity

**1. Adding a User**
1. Extract username and password.
2. Search `userTree` (AVL). If exists, throw `DuplicateUserException`.
3. Check `SecurityManager` (weak/leak). If weak, reject.
4. Create `User` object.
5. Insert into `userTree`.
6. Insert into `riskQueue` (base score 0).
7. Call `DatabaseManager::saveUser()`.
*Time Complexity: O(log N) for AVL insertion + O(1) for hash lookups.*

**2. Deleting a User**
1. Search `userTree` by username.
2. Remove node from `userTree`.
3. Search and remove `User*` from `riskQueue`.
4. Call `DatabaseManager::deleteUser()`.
*Time Complexity: O(log N) for AVL deletion + O(N) for Heap arbitrary deletion (can be optimized to O(log N) with an index map).*

**3. Updating a Password (with History & Risk)**
1. Check `leakedHashes` and `weakPasswords`.
2. Traverse user's `PasswordStack`. If match found, reject (Reuse error).
3. If valid, `push()` current password to `PasswordStack`.
4. Set new password.
5. Calculate new risk (e.g., +10 if they attempted a reused password first).
6. Update `riskQueue` (`increaseKey` or `decreaseKey`).
*Time Complexity: O(K) for Stack check (where K is max history) + O(1) hash lookups + O(log N) Heap update.*

**4. Detecting Leaks**
1. Receive raw password.
2. Compute SHA-256 hash.
3. Lookup hash in `leakedHashes`. Return `true` if found.
*Time Complexity: O(1) average case.*

**5. Calculating Risk**
1. `score = 0`.
2. If previous breach associated with user: `+50`.
3. If failed weak password attempt logged: `+20`.
4. Update score in `User` object, call `riskQueue.heapify()`.
*Time Complexity: O(1) calculation + O(log N) Heapify.*

---

### 5. Data Structures Justification

| DATA STRUCTURE | WHERE USED | WHY CHOSEN |
|---|---|---|
| **AVL BST** | User storage | $O(\log N)$ search/insert/delete. Balanced → no worst-case $O(N)$ skew. |
| **Hash Table** (`unordered_set`) | Leak database | $O(1)$ avg lookup. 500K+ hashes need instant check — no other DS beats this. |
| **Stack** (per user) | Password history | LIFO perfectly models "undo" behavior. $O(1)$ push/pop. |
| **Trie** | Weak password list | $O(L)$ prefix search. Can detect "password1", "password123" as same root. Space-efficient for common prefixes. |
| **Max-Heap** (`priority_queue`) | Risk prioritization | $O(1)$ get-max. Always know the MOST at-risk user instantly. |
| **Linked List** (`queue`) | Request queue | $O(1)$ enqueue/dequeue for batch processing pipeline. |

---

### 6. JSON Structures (For Logs & API Responses)

**User Profile Response:**
```json
{
  "userId": 1042,
  "username": "ali_hassan",
  "currentPassword": {
    "hashedPassword": "5e884898da28047151d0e56f8dc629277360",
    "timestamp": "2026-04-22T09:30:00Z",
    "wasLeaked": false,
    "wasWeak": false
  },
  "riskScore": 25.0,
  "riskLevel": "LOW",
  "createdAt": "2026-01-15T08:00:00Z",
  "lastUpdated": "2026-04-22T09:30:00Z",
  "isActive": true
}
```

**Password History List:**
```json
{
  "username": "ali_hassan",
  "history": [
    {
      "hashedPassword": "abc123hash...",
      "timestamp": "2026-01-15T08:00:00Z",
      "wasLeaked": true,
      "wasWeak": true,
      "riskAtTime": 65.0
    },
    {
      "hashedPassword": "def456hash...",
      "timestamp": "2026-03-01T12:00:00Z",
      "wasLeaked": false,
      "wasWeak": true,
      "riskAtTime": 40.0
    }
  ]
}
```

**Risk Report:**
```json
{
  "reportId": "RPT-2026-0422-001",
  "generatedAt": "2026-04-22T14:00:00Z",
  "topRiskUsers": [
    {
      "username": "bob_reuse",
      "riskScore": 85.0,
      "riskLevel": "CRITICAL",
      "flags": ["LEAKED", "WEAK", "REUSED"]
    },
    {
      "username": "sara_old",
      "riskScore": 55.0,
      "riskLevel": "HIGH",
      "flags": ["WEAK", "EXPIRED"]
    }
  ],
  "systemStats": {
    "totalUsers": 150,
    "criticalCount": 3,
    "highCount": 12,
    "mediumCount": 45,
    "lowCount": 90
  }
}
```

---

### 7. Project Folder Structure

```text
MBPLDS-DSA-Project-/
│
├── src/                    # Source files (.cpp)
│   ├── main.cpp            # Entry point
│   ├── core/               # Entities
│   │   ├── User.cpp
│   │   └── Password.cpp
│   ├── managers/           # Business Logic
│   │   ├── UserManager.cpp
│   │   ├── SecurityManager.cpp
│   │   └── RiskManager.cpp
│   ├── database/           # DB Connectivity
│   │   └── DatabaseManager.cpp
│   └── utils/              # Helper functions (Hashing)
│       └── HashUtils.cpp
│
├── include/                # Header files (.h)
│   ├── core/
│   ├── managers/
│   ├── database/
│   ├── utils/
│   └── datastructures/     # Custom Data Structures
│       ├── HashTable.h
│       ├── AVLTree.h
│       ├── MaxHeap.h
│       ├── Stack.h
│       └── Queue.h
│
├── data/                   # Mock data for testing
│   ├── weak_passwords.txt
│   └── mock_leaks_sha256.txt
│
├── docs/                   # Documentation and Diagrams
├── tests/                  # Unit tests (Catch2 or GoogleTest)
└── CMakeLists.txt          # Build configuration
```

---

### 8. Diagram Explanations (For Report Drawing)

1. **System Flow Diagram:** 
   - Draw a User on the left, sending data to an "API/Queue" block.
   - The Queue feeds into the "Main Processor".
   - The Processor has two-way arrows to "AVL Tree (Users)", "Hash Tables (Security)", and "Max-Heap (Risk)".
   - All components point down to a "MySQL Database" cylinder.
2. **Architecture / Class Relationship:**
   - Draw `UserManager` aggregating `User`.
   - Draw `User` composing `PasswordStack`.
   - Draw `RiskManager` referencing `User` pointers.
3. **Password Update Sequence Diagram:**
   - Actor (User) sends `update(pwd)` to `System`.
   - `System` queries `SecurityManager` -> returns `Safe`.
   - `System` queries `PasswordStack` -> returns `No Reuse`.
   - `System` pushes old pwd to stack.
   - `System` notifies `RiskManager` to adjust score.
   - `System` replies to Actor with `Success`.

---

### 9. Testing Strategy

- **Edge Cases:**
  - Pushing an empty string as a password.
  - Calling "Undo" when the password history stack is empty.
  - Attempting to add a user when the AVL tree is extremely unbalanced (tests the balancing logic).
- **Invalid Inputs:**
  - Special characters mapping to SQL injections (handled by parameterized queries in DBManager).
  - Extremely long passwords (>10,000 chars) testing memory limits.
- **Duplicate Handing:**
  - Inserting "UserA" twice. The BST must reject the second insertion in O(log N) without altering state.
- **Leak & Weak Passwords:**
  - Test exact matches (e.g., "password").
  - Test subset/variations (if similarity logic is implemented via Trie or Levenshtein distance).

---

### 10. Optimization & Error Handling

**Optimization Techniques:**
- **Lazy Loading:** Do not load all user password histories into RAM on startup. Only load a user's Stack from the DB when they actively attempt an update.
- **Pre-allocation:** Initialize the Hash Tables with a high bucket count based on the known size of the leak database to prevent expensive rehashing operations.
- **Pointer-Based Heap:** The Risk Max-Heap stores pointers (`User*`), not actual objects, preventing heavy memory copying when nodes swap during `heapify`.

**Error Handling:**
- **Custom Exceptions:** Implement classes like `UserNotFoundException`, `WeakPasswordException`, `StackEmptyException` for clean error routing.
- **Database Fallback:** If the MySQL connection drops, requests in the Queue are temporarily saved to a local JSON/CSV file and synced once the connection is restored.
- **Graceful Degradation:** If the leaked hash database is too large for RAM, fallback to an indexed file read (binary search on a sorted disk file) rather than crashing the system.
