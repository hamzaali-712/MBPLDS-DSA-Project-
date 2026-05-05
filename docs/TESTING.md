# Testing Strategy

| TEST CASE | INPUT | EXPECTED OUTPUT |
|---|---|---|
| Add valid user | "ahmed", "Str0ng#2026" | SUCCESS |
| Add duplicate user | "ahmed", "any" | FAIL: Exists |
| Add empty username | "", "password" | FAIL: Invalid |
| Add empty password | "user1", "" | FAIL: Invalid |
| Weak password | "user2", "123456" | WARN: Weak |
| Leaked password | "user3", "password" | WARN: Leaked |
| Both weak + leaked | "user4", "123456" | WARN: Both flags |
| Password reuse | Change to old hash | FAIL: Reuse |
| Undo with history | After 1 update | SUCCESS: Restored |
| Undo with no history | New user, no changes | FAIL: No history |
| Search existing user | "ahmed" | Return User* |
| Search missing user | "notexist" | Return nullptr |
| Delete existing user | "ahmed" | SUCCESS |
| Delete missing user | "ghost" | FAIL: Not found |
| Top risk users (N=3) | 10 users in system | Top 3 by score |
| Risk: leaked pwd | user with leaked pwd | Score ≥ 40 |
| Risk: old password | last changed >90 days | Score gets +10 |
| BST: 1000 users insert | Bulk insert | All O(log n) |
| Hash table: 500K lookups | Large leak dataset | All O(1) |
| Trie: prefix match | "pass", "password123" | Both detected |
| SQL injection attempt | "ali'; DROP TABLE--" | Sanitized/blocked |
| Very long password | 1000 char password | Handled gracefully |
| Special char username | "a@b!c" | FAIL: Invalid |
