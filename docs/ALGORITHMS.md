# Core System Algorithms

This document outlines the primary algorithms used within the MBPLDS architecture.

## ALGORITHM: Real Cryptographic SHA-256 Hashing
*Developed & Tested by: Farukh Mumtaz*

**INPUT:** `plainPassword` (string)  
**OUTPUT:** `hash` (64-character hex string)

**Step 1: Initialization**
- Initialize 8 hash values (state array) with the first 32 bits of the fractional parts of the square roots of the first 8 primes.
- Initialize array of 64 constants `K`.

**Step 2: Pre-processing (Padding)**
- Append the bit '1' to the message.
- Append '0' bits until message length in bits $\equiv 448 \pmod{512}$.
- Append length of original message as a 64-bit big-endian integer.

**Step 3: Chunk Processing**
- Break message into 512-bit chunks.
- For each chunk:
  - Create a 64-entry message schedule array `w[0..63]`.
  - Initialize working variables `a` to `h` with the current hash value.
  - Apply the SHA-256 compression function (using `CH`, `MAJ`, `SIG0`, `SIG1`, `EP0`, `EP1` bitwise operations) for 64 rounds.
  - Add the compressed chunk to the current hash value.

**Step 4: Output**
- Produce the final hash by converting the 8 state variables into a 64-character hexadecimal string.
- **Time Complexity:** $O(L)$ where $L$ = password length

## ALGORITHM: Case-Insensitive Substring Weak Pattern Detection (Trie)
*Optimized & Integrated by: Hamza Ali*

**INPUT:** `plainPassword` (string)  
**OUTPUT:** `isWeak` (bool)

**Step 1: Normalization**
- Convert `plainPassword` to lowercase to ensure case-insensitive matching.
- **Time:** $O(L)$

**Step 2: Substring Pattern Matching**
- For every character index `i` from $0$ to $L-1$:
  - Start at the `root` of the `WeakPasswordTrie`.
  - For every character index `j` from `i` to $L-1$:
    - Check if the character exists in the current TrieNode's children.
    - If no, `break` the inner loop and advance `i`.
    - If yes, traverse to the child node.
    - If the child node is marked `isEndOfWord`, `RETURN true` (Pattern found).
- **Time Complexity:** $O(L^2)$ in the worst case, but practically bounded by the small length of passwords.

## ALGORITHM: AddUser(username, plainPassword)

**Step 1: Validate username**
- **Time:** $O(|username|)$

**Step 2: Check duplicate**
- Call `UserBST.search(username)`
- **Time:** $O(\log n)$

**Step 3: Hash the password**
- `hash = HashUtils::generateSHA256(plainPassword)`
- **Time:** $O(L)$

**Step 4: Check leak**
- `isLeaked = LeakHashTable.isLeaked(hash)`
- **Time:** $O(1)$ average

**Step 5: Check weakness**
- `isWeak = WeakPasswordTrie.containsPattern(plainPassword)`
- **Time:** $O(L^2)$

**Step 6: Insert into BST & RiskHeap**
- `UserBST.insert(user)`
- If risk > threshold, `RiskMaxHeap.push(user)`
- **Time:** $O(\log n)$

## TIME COMPLEXITY SUMMARY

| OPERATION | TIME COMPLEXITY | NOTES |
|---|---|---|
| Add User | $O(\log n + L^2)$ | BST + Substring Trie |
| Delete User | $O(\log n)$ | BST rebalance |
| Search User | $O(\log n)$ | BST |
| Generate SHA-256 | $O(L)$ | Bitwise chunks |
| Check Leak | $O(1)$ average | Hash table lookup |
| Check Weak Pattern | $O(L^2)$ | Trie substring matching |
| Calculate Risk | $O(1)$ | Mathematical combinations |
