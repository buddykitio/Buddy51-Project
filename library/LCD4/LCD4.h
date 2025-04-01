#ifndef __LCD_H__
#define __LCD_H__

#include <8051.h>          // 8051 microcontroller header
#include "../type.h"       // Custom type definitions (likely contains u8, u16 etc.)
#include "../Delay/Delay.h"// Delay function declarations

/* Pin Definitions - Modify these based on your hardware connections */
#define LCD_RS P2_2       // Register Select (Command/Data)
#define LCD_EN P2_3        // Enable pin (clock signal)
#define LCD_D4 P2_4        // Data bit 4
#define LCD_D5 P2_5        // Data bit 5
#define LCD_D6 P2_6        // Data bit 6
#define LCD_D7 P2_7        // Data bit 7

/* LCD Command Set */
#define LCD_CLEAR         0x01 // Clear display and return home
#define LCD_HOME          0x02 // Return cursor to home position
#define LCD_ENTRYMODESET  0x04 // Set text entry mode
#define LCD_DISPLAYCTRL   0x08 // Display on/off control
#define LCD_CURSORSHIFT   0x10 // Cursor/display shift control
#define LCD_FUNCTIONSET   0x20 // Function set (interface, lines, font)
#define LCD_SETCGRAMADDR  0x40 // Set CGRAM address (custom characters)
#define LCD_SETDDRAMADDR  0x80 // Set DDRAM address (display RAM)

/* Entry Mode Flags (Used with LCD_ENTRYMODESET) */

#define LCD_ENTRYLEFT     0x02 // Left-to-right text direction
#define LCD_ENTRYSHIFTINC 0x01 // Auto-increment cursor position

/* Display/Cursor Shift Flags (Used with LCD_CURSORSHIFT) */

#define LCD_DISPLAYMOVE   0x08 // Move display instead of cursor
#define LCD_MOVERIGHT     0x04 // Move right (for display/cursor)
#define LCD_MOVELEFT      0x00 // Move left (for display/cursor)

/* Display Control Flags (Used with LCD_DISPLAYCTRL) */

#define LCD_DISPLAYON     0x04 // Turn display on
#define LCD_CURSORON      0x02 // Turn cursor on
#define LCD_BLINKON       0x01 // Turn cursor blinking on

/* Function Set Flags (Used with LCD_FUNCTIONSET) */
#define LCD_4BITMODE      0x00 // 4-bit interface mode
#define LCD_2LINE         0x08 // 2-line display mode
#define LCD_5x10DOTS      0x04 // 5x10 dot character font
#define LCD_5x8DOTS       0x00 // 5x8 dot character font (standard)

/* LCD Dimensions - Modify for different display sizes */
#define LCD_ROWS 2        // Number of display rows
#define LCD_COLS 16       // Number of columns per row

/* Function Prototypes */
void LCD_Command(u8 cmd);         // Send command to LCD
void LCD_Data(u8 dat);            // Send data to LCD
void LCD_Init(void);              // Initialize LCD
void LCD_Puts(pu8 ptr);   // Print string to LCD
void LCD_Goto(u8 r, u8 c);        // Move cursor to (row, column)
void LCD_Clear(u8 row, u8 col, u8 size); // Clear portion of display
void LCD_ScrollLeft(void);        // Scroll display left
void LCD_ScrollRight(void);       // Scroll display right
void LCD_LeftToRight(void);       // Set left-to-right text direction
void LCD_RightToLeft(void);       // Set right-to-left text direction
void LCD_Autoscroll(void);        // Enable auto-scrolling
void LCD_NoAutoscroll(void);      // Disable auto-scrolling

#endif 