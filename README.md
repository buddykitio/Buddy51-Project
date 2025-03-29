# Empty SDCC Project for 8051 Development

This is an empty project template for **SDCC (Small Device C Compiler)** based 8051 development. Just add your C source files to the `src/` directory and run the build script!

---

## 📂 **Project Structure**
```
├── src/        # Add your .c and .h files here
├── object/     # Compiled object (.rel) files (auto-created)
├── release/    # Final HEX output (auto-created)
├── build.bat   # Windows build script
├── build.sh    # Linux/MacOS build script
├── clean.bat   # Windows clean script
├── clean.sh    # Linux/MacOS clean script
└── README.md   # Project documentation
```

---

## ⚙️ **How to Build**

### **🔹 Windows**
1. Open **Command Prompt (cmd)**
2. Run:
   ```cmd
   build.bat
   ```

### **🔹 Linux & MacOS**
1. Open **Terminal**
2. Give execute permission (only first time):
   ```bash
   chmod +x build.sh
   ```
3. Run:
   ```bash
   ./build.sh
   ```

---

## 🧹 **How to Clean Build Files**

### **🔹 Windows**
```cmd
clean.bat
```

### **🔹 Linux & MacOS**
```bash
./clean.sh
```

---

## 📢 **Notes**
- **Make sure SDCC is installed and available in your system's PATH.**
- Place all your `.c` and `.h` files inside the `src/` folder.
- The compiled HEX file will be available in the `release/` folder.

🚀 **Happy Coding!**

