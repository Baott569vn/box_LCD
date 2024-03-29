#include "menuDisplay.h"
#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "customCharacters.h"

// Địa chỉ và kích thước của màn hình LCD I2C
#define I2C_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// Khai báo đối tượng LiquidCrystal_I2C với địa chỉ và kích thước đã định sẵn
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

// Constructor cho class menuDisplay
menuDisplay::menuDisplay()
{
}

byte menuDisplay::_select_User()
{
    byte select_User = (sizeof(_LCD_Arduino.select_User) / sizeof(_LCD_Arduino.select_User[0])) - 3;
    return select_User;
}

byte menuDisplay::_select_Mode()
{
    byte select_Mode = (sizeof(_LCD_Arduino.select_Mode) / sizeof(_LCD_Arduino.select_Mode[0])) - 3;
    return select_Mode;
}

// Hàm khởi tạo LCD và hiển thị màn hình khởi động
void menuDisplay::begin()
{
    lcd.init();
    lcd.backlight();

    // Tải ký tự tại địa chỉ 0 và 1 từ thư viện
    for (int characterMax = 0; characterMax < sizeof(Characters) / sizeof(Characters[0]); characterMax++)
    {
        lcd.createChar(characterMax, (uint8_t *)Characters[characterMax]);
    }

    // Màn hình khởi động
    lcd.setCursor(0, 0);
    lcd.print(_LCD_Arduino.messageLCD[0]);
    lcd.setCursor(0, 1);
    lcd.write(1); // Hiển thị ký tự tùy chỉnh

    delay(2000);

    // Cuộn văn bản sang trái
    for (int positionCounte{0}; positionCounte < _LCD_Arduino.messageLCD[0].length(); positionCounte++)
    {
        lcd.scrollDisplayLeft();
        delay(50);
    }

    lcd.clear();

    // Hiển thị màn hình thứ hai
    lcd.setCursor(0, 0);
    lcd.print(_LCD_Arduino.messageLCD[1]);
    delay(2000);

    // Cuộn văn bản sang trái
    for (int positionCounte{0}; positionCounte < _LCD_Arduino.messageLCD[1].length(); positionCounte++)
    {
        lcd.scrollDisplayLeft();
        delay(50);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(_LCD_Arduino.select_User[0]);
    delay(500);
}

// Hiển thị tất cả các menu dựa trên chủ đề và chế độ
void menuDisplay::menuShowAll(byte munberTheme, byte selectMode)
{
    switch (munberTheme)
    {
    case 1:
        menuShow1(selectMode);
        break;
    case 2:
        menuShow2(selectMode);
        break;
    default:
        break;
    }
}

// Hiển thị menu 1 dựa trên lựa chọn
void menuDisplay::menuShow1(byte selec)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(_LCD_Arduino.select_User[0]);

    switch (selec)
    {
    case 1:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_Mode[0]);
        break;
    case 2:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_Mode[1]);
        break;
    case 3:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_Mode[2]);
        break;
    case 4:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_Mode[3]);
        break;
    default:
        break;
    }
}

// Hiển thị menu 1 dựa trên lựa chọn
void menuDisplay::menuShow2(byte selec)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(_LCD_Arduino.select_User[0]);

    switch (selec)
    {
    case 1:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_User[2]); // Mode_Bas
        lcd.setCursor(15, 1);
        lcd.write(1);
        break;
    case 2:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_User[3]); // Faker
        lcd.setCursor(15, 1);
        lcd.write(8);
        break;
    case 3:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_User[4]); //Attach
        lcd.setCursor(15, 1);
        lcd.write(5);
        break;
    case 4:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_User[5]); //Wireless
        lcd.setCursor(15, 1);
        lcd.write(7);
        break;
    case 5:
        lcd.setCursor(8, 0);
        lcd.print(_LCD_Arduino.select_User[6]); //About
        lcd.setCursor(15, 1);
        lcd.write(6);
        break;
    default:
        break;
    }
}
