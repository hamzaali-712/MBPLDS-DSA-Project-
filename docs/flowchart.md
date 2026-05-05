# System Flow Diagram

```mermaid
flowchart TD
    Start([START]) --> UI[Streamlit UI Input: Password]
    UI --> UI_Check{Is Empty?}
    UI_Check -- yes --> UI_Err[Show Warning]
    UI_Err --> End([END])
    UI_Check -- no --> Exec[Execute ./mbplds --analyze]
    
    Exec --> CppStart[C++ Engine Starts]
    CppStart --> LoadFiles[Load weak_passwords.txt & leaked_hashes.txt]
    LoadFiles --> Hash[Generate Real SHA-256 via HashUtils]
    
    Hash --> CheckLeak{Check Hash in LeakHashTable}
    CheckLeak -- leaked --> FlagLeak[isLeaked = true]
    CheckLeak -- safe --> FlagSafeLeak[isLeaked = false]
    
    FlagLeak --> CheckWeak
    FlagSafeLeak --> CheckWeak
    
    CheckWeak{Substring Match in WeakPasswordTrie}
    CheckWeak -- weak --> FlagWeak[isWeak = true]
    CheckWeak -- safe --> FlagSafeWeak[isWeak = false]
    
    FlagWeak --> CalcEnt
    FlagSafeWeak --> CalcEnt
    
    CalcEnt[Calculate Mathematical Entropy & Crack Time]
    CalcEnt --> OutJSON[Print JSON Output to stdout]
    
    OutJSON --> PyParse[Python json.loads()]
    PyParse --> UIRender[Render Metrics & Altair Graphs]
    
    UIRender --> AI_Check{Click AI Report?}
    AI_Check -- no --> End
    AI_Check -- yes --> CallGroq[Send Data to Groq llama-3.1-8b-instant]
    CallGroq --> RenderReport[Display AI Security Report]
    RenderReport --> End
```
