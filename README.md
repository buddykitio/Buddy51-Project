# SDCC 8051 Development Library

This is a complete 8051 project template for **SDCC (Small Device C Compiler)**-based 8051 development. Simply add your C source files to the `src/` directory and run the build script!

---

## 📂 **Project Structure**
```
├── src/          # Add your .c and .h files here
├── library/      # Fully functional libraries
├──── Delay       # Delay function routines
├──── DS1307      # I2C based DS1307 RTC Library
├──── EEPROM      # I2C based 24C02/04/08/16 EEPROM memory library
├──── I2C         # I2C communication library
├──── PCF8591     # I2C based ADC library
├──── MPU6050     # I2C based MPU 6050 library
├──── KEYPAD4X4   # 4x4 matrix keypad library
├──── LCD4        # 4-bit LCD parallel & I2C supported library
├──── LED7SEGMENT # 6 digit, 7 segment with dot and negative support library
├──── SPI         # Software driven SPI for periperals
├── object/       # Compiled object (.rel) files (auto-created)
├── release/      # Final HEX output (auto-created)
├── build.bat     # Windows build script
├── build.sh      # Linux/MacOS build script
├── clean.bat     # Windows clean script
├── clean.sh      # Linux/MacOS clean script
└── README.md     # Project documentation
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

## ⚙️ **How to Install Nuvoton ISP**
Novoton ISP is required to flash code.

1. Download Nuvoton ISP from the [Nuvoton 8051 ISP Official Website](https://www.nuvoton.com/resource-download.jsp?tp_GUID=SW0320120105135349).
2. Verify the installation.

## ⚙️ **How to Install VScode**
  VScode is required to edit code.

  1. Click here to download [VScode Official](https://code.visualstudio.com/download#)

 2. Verify the installation.

   
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
