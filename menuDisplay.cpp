#include "menuDisplay.h"
#include <stdint.h> // Để sử dụng uint8_t
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

#define I2C_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

menuDisplay::menuDisplay()
{
}

void menuDisplay::begin()
{
    lcd.init();
    lcd.backlight();
    // Tải ký tự tại địa chỉ 0 và 1 từ thư viện
    for (int characterMax{0}; characterMax < sizeof(customCharacters) / sizeof(customCharacters[0]); characterMax++)
    {
        lcd.createChar(characterMax, (uint8_t *)customCharacters[characterMax]);
    }

    // màng hình khởi động
    lcd.setCursor(0, 0);
    lcd.println(_LCD_Arduino.messageLCD[0]);
    lcd.setCursor(0, 1);
    lcd.write(1);
    delay(2000);

    for (int positionCounte{0}; positionCounte < _LCD_Arduino.messageLCD[0].length(); positionCounte++)
    {
        lcd.scrollDisplayLeft();
        delay(50);
    }
    //
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(_LCD_Arduino.messageLCD[1]);
    delay(2000);
    //
    for (int positionCounte{0}; positionCounte < _LCD_Arduino.messageLCD[1].length(); positionCounte++)
    {
        lcd.scrollDisplayLeft();
        delay(50);
    }
    //
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(_LCD_Arduino.select_User[0]);
    delay(500);
}

void menuDisplay::menuShowAll(byte munberTheme, byte selectMode)
{
    _LCD_Arduino._munberTheme = munberTheme;
    _LCD_Arduino.selectMode = selectMode;
    switch (_LCD_Arduino._munberTheme)
    {
    case 1:
        menuShow1(_LCD_Arduino.selectMode);
        break;
    default:
        break;
    }
}

void menuDisplay::menuShow1(byte selec)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(_LCD_Arduino.select_User[0]);
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
