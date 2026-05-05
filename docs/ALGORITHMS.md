# Core System Algorithms

## ALGORITHM: AddUser(username, plainPassword)

**INPUT:** `username` (string), `plainPassword` (string)  
**OUTPUT:** `success/failure` (bool)

**Step 1: Validate username**
- If length < 3 OR contains special chars → `RETURN false`
- **Time:** $O(|username|)$

**Step 2: Check duplicate**
- Call `UserBST.search(username)`
- If found → `RETURN false` ("User already exists")
- **Time:** $O(\log n)$

**Step 3: Hash the password**
- `hash = PasswordEngine.hashPassword(plainPassword)`
- **Time:** $O(L)$ where $L$ = password length

**Step 4: Check leak**
- `isLeaked = LeakHashTable.isLeaked(hash)`
- **Time:** $O(1)$ average

**Step 5: Check weakness**
- `isWeak = WeakPasswordTrie.isWeak(plainPassword)`
- **Time:** $O(L)$

**Step 6: Build PasswordRecord**
- `record = {hash, plain, now(), isLeaked, isWeak}`

**Step 7: Create User object**
- `user = new User(nextId++, username, record)`

**Step 8: Calculate initial risk score**
- `score = PasswordEngine.calculateRisk(user)`
- `user.riskScore = score`

**Step 9: Insert into BST**
- `UserBST.insertUser(user)`
- **Time:** $O(\log n)$

**Step 10: Push to RiskHeap if score > threshold**
- If score > 40.0 → `RiskMaxHeap.pushUser(username, score)`
- **Time:** $O(\log n)$

**Step 11: Persist to database**
- `DatabaseManager.saveUser(user)`
- **Time:** $O(1)$ DB write

**Step 12: Return**
- `RETURN true`

---
**TOTAL TIME COMPLEXITY:** $O(\log n + L)$  
**SPACE COMPLEXITY:** $O(1)$ additional

## ALGORITHM: DeleteUser(username)

**Step 1: Search BST for username**
- `user = UserBST.search(username)`
- If null → `RETURN false`
- **Time:** $O(\log n)$

**Step 2: Remove from BST**
- `UserBST.deleteUser(username)`
- **Time:** $O(\log n)$

**Step 3: Mark deleted in DB (soft delete)**
- `DatabaseManager.deleteUser(username)`
- **Time:** $O(1)$

**Step 4: Note: RiskHeap uses lazy deletion**
- Score map entry removed
- Heap node becomes stale → filtered on next pop
- **Time:** $O(1)$

**Step 5: Free memory**
- `delete user pointer`
- **Time:** $O(1)$

---
**TOTAL TIME COMPLEXITY:** $O(\log n)$

## ALGORITHM: UpdatePassword(username, newPlainPassword)

**Step 1: Search for user**
- `user = UserBST.search(username)`
- If null → `RETURN false`
- **Time:** $O(\log n)$

**Step 2: Hash new password**
- `newHash = PasswordEngine.hashPassword(newPlainPassword)`
- **Time:** $O(L)$

**Step 3: Check reuse against history**
- If `PasswordHistory.contains(newHash)` → `RETURN false` ("Reuse detected")
- **Time:** $O(k)$ where $k$ = history size (max 10)

**Step 4: Check leak**
- If `LeakHashTable.isLeaked(newHash)` → flag but allow with warning
- **Time:** $O(1)$

**Step 5: Check weakness**
- If `WeakPasswordTrie.isWeak(newPlainPassword)` → flag with warning
- **Time:** $O(L)$

**Step 6: Push current password to history stack**
- `user.history.push(user.currentPassword)`
- **Time:** $O(1)$

**Step 7: Set new current password**
- `user.currentPassword = new PasswordRecord(...)`
- **Time:** $O(1)$

**Step 8: Recalculate risk**
- `newScore = PasswordEngine.calculateRisk(user)`
- `user.riskScore = newScore`
- `RiskMaxHeap.updateScore(username, newScore)`
- **Time:** $O(\log n)$

**Step 9: Persist**
- `DatabaseManager.updateUser(user)`
- `DatabaseManager.savePasswordRecord(username, newRecord)`
- **Time:** $O(1)$

**Step 10: Return**
- `RETURN true`

---
**TOTAL TIME COMPLEXITY:** $O(\log n + L + k) \approx O(\log n)$

## ALGORITHM: UndoPasswordChange(username)

**Step 1: Find user in BST**
- **Time:** $O(\log n)$

**Step 2: Check if history stack is non-empty**
- If `user.history.size() == 0` → `RETURN false` ("No history")
- **Time:** $O(1)$

**Step 3: Pop last record from stack**
- `previousRecord = user.history.undo()`
- **Time:** $O(1)$

**Step 4: Restore as current password**
- `user.currentPassword = previousRecord`
- **Time:** $O(1)$

**Step 5: Recalculate risk with restored password**
- **Time:** $O(\log n)$ for heap update

**Step 6: Sync to database**
- **Time:** $O(1)$

---
**TOTAL TIME COMPLEXITY:** $O(\log n)$

## ALGORITHM: DetectLeak(plainPassword)

**Step 1: Hash the input password**
- `hash = hashPassword(plainPassword)`
- **Time:** $O(L)$

**Step 2: Query LeakHashTable**
- `result = leakDB.isLeaked(hash)`
- **Time:** $O(1)$ average — unordered_set lookup

**Step 3: Return result with severity**
- If found → `return {LEAKED, HIGH_RISK}`
- Else → `return {CLEAN, NO_RISK}`

---
**TOTAL TIME COMPLEXITY:** $O(L)$  
**SPACE:** $O(1)$ additional

## ALGORITHM: CalculateRisk(user)

Risk Score = Weighted sum of 5 factors (0–100 scale)

**Factor 1: Leaked Password (Weight: 40 points)**
- If `currentPassword.wasLeaked == true` → +40

**Factor 2: Weak Password (Weight: 25 points)**
- If `currentPassword.wasWeak == true` → +25

**Factor 3: Password Reuse in History (Weight: 20 points)**
- Count reuse occurrences in history stack
- `reuseScore = (reuseCount / historySize) * 20`

**Factor 4: Password Age (Weight: 10 points)**
- `daysSinceChange = (now - lastUpdated) / 86400`
- If days > 90 → +10
- If days > 180 → +10 (capped at 10)

**Factor 5: History Pattern (Weight: 5 points)**
- If all history passwords were weak → +5

**FINAL SCORE** = sum of all factors (capped at 100)

**Risk Level Classification:**
- 0–25   → "LOW"
- 26–50  → "MEDIUM"
- 51–75  → "HIGH"
- 76–100 → "CRITICAL"

---
**TIME COMPLEXITY:** $O(k)$ where $k$ = history size ($\le 10$) $\rightarrow O(1)$ amortized

## TIME COMPLEXITY SUMMARY

| OPERATION | TIME COMPLEXITY | NOTES |
|---|---|---|
| Add User | $O(\log n + L)$ | BST + hash |
| Delete User | $O(\log n)$ | AVL rebalance |
| Search User | $O(\log n)$ | AVL BST |
| Update Password | $O(\log n + L + k)$ | $k \le 10 \rightarrow O(1)$ |
| Undo Password | $O(\log n)$ | Stack $O(1)$ |
| Check Leak | $O(1)$ average | Hash table |
| Check Weak Password | $O(L)$ | Trie traversal |
| Calculate Risk | $O(k) \approx O(1)$ | $k \le 10$ history |
| Get Top-N Risk Users | $O(N \log H)$ | Heap pops |
| Load from DB | $O(n \log n)$ | $n$ BST inserts |
| Bulk Leak Check (m) | $O(m)$ | $m$ hash lookups |
| All Users (in-order) | $O(n)$ | BST traversal |
| Push to Risk Heap | $O(\log H)$ | $H$ = heap size |
