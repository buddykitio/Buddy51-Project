# SDCC Compiler-Supported Complete 8051 Development Library

This is a complete 8051 project template for **SDCC (Small Device C Compiler)**-based 8051 development. Simply add your C source files to the `src/` directory and run the build script!

---

## 📂 **Project Structure**
```
├── src/        # Add your .c and .h files here
├── library/    # Fully functional libraries
├──── Delay     # Delay function routines
├──── LCD4      # 4-bit LCD library and functions
├── object/     # Compiled object (.rel) files (auto-created)
├── release/    # Final HEX output (auto-created)
├── build.bat   # Windows build script
├── build.sh    # Linux/MacOS build script
├── clean.bat   # Windows clean script
├── clean.sh    # Linux/MacOS clean script
└── README.md   # Project documentation
```

---

## ⚙️ **How to Install SDCC**
SDCC (Small Device C Compiler) is required to build the project.

### **🔹 Windows**
1. Download SDCC from the [SDCC Official Website](https://sourceforge.net/projects/sdcc/).
2. Install it and ensure `sdcc` is added to the system's `PATH`.
3. Verify the installation by running:
   ```cmd
   sdcc --version
   ```

### **🔹 Linux (Debian/Ubuntu)**
```bash
sudo apt update
sudo apt install sdcc
sdcc --version
```

### **🔹 MacOS (Using Homebrew)**
```bash
brew install sdcc
sdcc --version
```

---

## ⚙️ **How to Build**

### **🔹 Windows**
1. Open **Command Prompt (cmd)**.
2. Run:
   ```cmd
   build.bat
   ```

### **🔹 Linux & MacOS**
1. Open **Terminal**.
2. Grant execute permission (only required once):
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
- **Ensure SDCC is installed and available in your system's PATH.**
- Place all your `.c` and `.h` files inside the `src/` folder.
- The compiled HEX file will be available in the `release/` folder.

🚀 **Happy Coding!**