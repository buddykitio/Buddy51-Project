#include "LCD4.H"

u8 _displaymode = 0x00; // Default: Left-to-right, no autoscroll

void LCD_Nibble(u8 data) {
    LCD_D7 = (data & 0x08) ? 1 : 0;
    LCD_D6 = (data & 0x04) ? 1 : 0;
    LCD_D5 = (data & 0x02) ? 1 : 0;
    LCD_D4 = (data & 0x01) ? 1 : 0;

    LCD_EN = 0;
    DelayXus(1);
    LCD_EN = 1;
    DelayXus(5);
    LCD_EN = 0;
    DelayXus(100);
}

// Send command to LCD
void LCD_Command(u8 cmd) {
    LCD_RS = 0;
    LCD_Nibble((cmd >> 4) & 0x0F);
    LCD_Nibble(cmd & 0x0F);
    if (cmd == LCD_CLEAR) DelayXus(2000);
    else DelayXus(50);
}

// Send data to LCD
void LCD_Data(u8 dat) {
    LCD_RS = 1;
    LCD_Nibble((dat >> 4) & 0x0F);
    LCD_Nibble(dat & 0x0F);
    DelayXus(50);
}

// Initialize LCD
void LCD_Init(void) {  
    P2 = 0x00;
    P2 = 0xFF; // Configure as push-pull

    DelayXus(50000);  
    LCD_RS = 0;
    LCD_EN = 0;  

    // Reset sequence
    LCD_Nibble(0x03);
    DelayXus(4500);
    LCD_Nibble(0x03);
    DelayXus(4500);
    LCD_Nibble(0x03);
    DelayXus(150); 

    LCD_Nibble(0x02);    // Switch to 4-bit mode
    DelayXus(150);

    LCD_Command(0x28);   // Function set: 4-bit, 2-line, 5x8 dots 
    LCD_Command(0x0C);   // Display on, cursor off 
    LCD_Command(0x01);   // Clear display
    LCD_Command(LCD_ENTRYMODESET | _displaymode); // Default mode
}

// Print a string
void LCD_Puts(pu8 ptr) {
    while (*ptr) {
        LCD_Data(*ptr++);
    }
}

// Move cursor to (row, column)
void LCD_Goto(u8 r, u8 c) {
    if (r == 1) {
        LCD_Command(0x80 + c);
    } else {
        LCD_Command(0xC0 + c);
    }
}

// Clear part of the display
void LCD_Clear(u8 row, u8 col, u8 size) {
    LCD_Goto(row, col);
    if (size + col > LCD_COLS)
        size = LCD_COLS - col;
    while (size--) {
        LCD_Data(' ');
    }
    LCD_Goto(row, col);
}

// Scroll display left 
void LCD_ScrollLeft(void) {
    LCD_Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

// Scroll display right 
void LCD_ScrollRight(void) {
    LCD_Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// Set left-to-right text direction
void LCD_LeftToRight(void) {
    _displaymode |= LCD_ENTRYLEFT;
    LCD_Command(LCD_ENTRYMODESET | _displaymode);
}

// Set right-to-left text direction
void LCD_RightToLeft(void) {
    _displaymode &= ~LCD_ENTRYLEFT;
    LCD_Command(LCD_ENTRYMODESET | _displaymode);
}

// Enable autoscroll (text shifts automatically)
void LCD_Autoscroll(void) {
    _displaymode |= LCD_ENTRYSHIFTINC;
    LCD_Command(LCD_ENTRYMODESET | _displaymode);
}

// Disable autoscroll (default)
void LCD_NoAutoscroll(void) {
    _displaymode &= ~LCD_ENTRYSHIFTINC;
    LCD_Command(LCD_ENTRYMODESET | _displaymode);
}