# 🔐 Passwordingding

This project is a **secure password generator written in C**.  
It uses **cryptographically secure randomness from `/dev/urandom`** and guarantees that every generated password contains:
- Lowercase letters  
- Uppercase letters  
- Digits  
- Symbols  

> ⚠️ This project is for educational purposes.

---

## 🚀 Features

- Cryptographically secure randomness using `/dev/urandom`
- **Unbiased random number generation (rejection sampling to prevent modulo bias)**
- Guarantees at least one:
  - lowercase letter  
  - uppercase letter  
  - digit  
  - symbol  
- Minimum password length: 12 characters
- Fisher–Yates shuffle to prevent predictable patterns
- Linux / macOS compatible
- Clean, readable, and extensible C code

---

## 📸 Example Output

```bash
Enter password length (min 12): 16
Generated password: A@fP7kR!x2LmQ9Zs
