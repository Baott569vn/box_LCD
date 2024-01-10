#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

#include "Arduino.h"
#include <stdint.h> // Để sử dụng uint8_t

// Ký tự tùy chỉnh cho LCD
const uint8_t customCharacters[][8] = {
    {0x00, 0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04}, // Ký tự 0: heart
    {0x11, 0x1B, 0x1B, 0x00, 0x11, 0x1F, 0x1F, 0x0E}, // Ký tự 1: baott569
    {0x02, 0x06, 0x0F, 0x1F, 0x1F, 0x1F, 0x0E, 0x00}, // Ký tự 2: hot
    {0x04, 0x15, 0x0E, 0x1F, 0x0E, 0x15, 0x04, 0x00}, // Ký tự 3: cool
    {0x07, 0x08, 0x10, 0x08, 0x08, 0x08, 0x08, 0x0F}, // Ký tự 4: left home
    {0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}, // Ký tự 5: mid home
    {0x1C, 0x02, 0x01, 0x02, 0x1A, 0x1A, 0x1A, 0x1A}, // Ký tự 6: right home
    {0x00, 0x02, 0x15, 0x08, 0x02, 0x15, 0x08, 0x00}  // Ký tự 7: miod temp
    // Thêm các ký tự khác nếu cần
};

class menuDisplay
{
private:
    struct
    {
        String messageLCD[2] = {
            "BAOTT569_IOT",
            "System_check",
        };
        String select_User[4] = {
            "Select: ",
            "MODE> ",
            " <",
            "<SET"};
        String select_Mode[4] = {
            "Temp",
            "Hum",
            "Counter",
            "Battery"};
        byte _munberTheme, selectMode;
    } _LCD_Arduino;

public:
    menuDisplay();                                       // Constructor
    void begin();                                        // Khởi tạo LCD
    void menuShowAll(byte munberTheme, byte selectMode); // Hiển thị tất cả các menu
    void menuShow1(byte selec);                          // Hiển thị menu 1
};

#endif // MENU_DISPLAY_H
