# Class Relationship Diagram

```mermaid
classDiagram
    class User
    class PasswordRecord
    class PasswordHistory
    class UserManager
    class UserBST
    class LeakHashTable
    class WeakPasswordTrie
    class RiskMaxHeap
    class PasswordEngine
    class DatabaseManager

    User *-- PasswordRecord : has-a
    User *-- PasswordHistory : has-a (stack<PasswordRecord>)
    UserManager *-- UserBST : contains
    UserManager *-- LeakHashTable : contains
    UserManager *-- WeakPasswordTrie : contains
    UserManager *-- RiskMaxHeap : contains
    UserManager ..> PasswordEngine : uses
    UserManager ..> DatabaseManager : depends-on
    PasswordEngine ..> LeakHashTable : uses
    PasswordEngine ..> WeakPasswordTrie : uses
```
