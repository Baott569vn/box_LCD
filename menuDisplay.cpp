#include "menuDisplay.h"
#include <stdint.h> // Để sử dụng uint8_t
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "CustomLCD.h"
#include "Arduino.h"

#define I2C_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

menuDisplay::menuDisplay(byte munberTheme, byte selectMode)
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

void menuDisplay::begin()
{
    lcd.init();
    lcd.backlight();
    // Tải ký tự tại địa chỉ 0 và 1 từ thư viện
    for (int characterMax{0}; characterMax < sizeof(customCharacters) / sizeof(customCharacters[0]); ++characterMax)
    {
        lcd.createChar(characterMax, (uint8_t *)customCharacters[characterMax]);
    }
    // màng hình khởi động
    lcd.setCursor(-1, 0);
    lcd.println(_LCD_Arduino.messageLCD[0]);
    for (int positionCounte = 0; positionCounte < _LCD_Arduino.messageLCD[0].length(); positionCounte++)
    {
        lcd.scrollDisplayRight();
        delay(300);
    }
    lcd.clear();
    delay(1000);
    lcd.setCursor(-1, 0);
    lcd.println(_LCD_Arduino.messageLCD[1]);
    for (int positionCounte = 0; positionCounte < _LCD_Arduino.messageLCD[0].length(); positionCounte++)
    {
        lcd.scrollDisplayRight();
        delay(300);
    }
    delay(2000);
    lcd.clear();
}

void menuShow1(uint8_t Selec)
{
}
