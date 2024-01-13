#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

#include "Arduino.h"
#include <stdint.h> // Để sử dụng uint8_t

class menuDisplay
{
private:
    struct
    {
        String messageLCD[2] = {
            "BAOTT569_IOT",
            "System_check",
        };
        String select_User[7] = {
            "Select: ", // 0: Mô tả chức năng của mục lựa chọn
            "SET",      // 1: Mô tả chức năng của mục lựa chọn
            "Mode_Bas", // 2: Mô tả chức năng của mục lựa chọn
            "Faker",    // 3: Mô tả chức năng của mục lựa chọn
            "Attach",   // 4: Mô tả chức năng của mục lựa chọn
            "Wireless", // 5: Mô tả chức năng của mục lựa chọn
            "About"     // 6: Mô tả chức năng của mục lựa chọn
        };
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
    void menuShow2(byte selec);                          // Hiển thị menu 2
    byte _select_User();
    byte _select_Mode();
};

#endif // MENU_DISPLAY_H
