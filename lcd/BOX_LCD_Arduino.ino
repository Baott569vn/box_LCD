#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "CustomLCD.h"

#define I2C_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(A0));
  randomSeed(analogRead(A1));
  // Tải ký tự tại địa chỉ 0 và 1 từ thư viện
  lcd.createChar(0, (uint8_t *)customCharacters[0]);
  lcd.createChar(1, (uint8_t *)customCharacters[1]);
  lcd.createChar(2, (uint8_t *)customCharacters[2]);
  lcd.createChar(3, (uint8_t *)customCharacters[3]);
  lcd.createChar(4, (uint8_t *)customCharacters[4]);
  lcd.createChar(5, (uint8_t *)customCharacters[5]);
  lcd.createChar(6, (uint8_t *)customCharacters[6]);
  lcd.createChar(7, (uint8_t *)customCharacters[7]);
  // lcd.setCursor(0, 0);
  // lcd.write(0);
}

void homeChaR()
{
  lcd.setCursor(13, 1);
  lcd.write(4);
  lcd.setCursor(14, 1);
  lcd.write(5);
  lcd.setCursor(15, 1);
  lcd.write(6);
}

void loop()
{
  long valueRand1 = random(0, 100 + 1);
  long valueRand2 = random(0, 100 + 1);

  lcd.clear();

  // Định dạng chuỗi và in lên LCD
  char tempStr[5];
  sprintf(tempStr, "TEMP: %02d", valueRand1);
  lcd.setCursor(0, 0);
  lcd.print(tempStr);

  char humStr[5];
  sprintf(humStr, "HUM:  %02d%%", valueRand2);
  lcd.setCursor(0, 1);
  lcd.print(humStr);

  /*%02ld: Định dạng giá trị số nguyên dạng long (ld) sao cho nó có ít nhất 2 chữ số và tự động thêm số 0 phía trước nếu giá trị có ít hơn.
    %02ld%%: Tương tự như trên, nhưng thêm dấu phần trăm vào cuối.
    Cụ thể:
    %: Ký tự đặc biệt để bắt đầu phần định dạng.
    0: Cho biết sử dụng số 0 để thêm vào phía trước nếu cần.
    2: Cho biết ít nhất phải có 2 chữ số.
    ld: Cho biết đây là định dạng cho giá trị kiểu long.*/

  homeChaR();

  if (valueRand1 > 60)
  {
    lcd.setCursor(8, 0);
    lcd.write(2);
  }
  else if (valueRand1 < 20)
  {
    lcd.setCursor(8, 0);
    lcd.write(3);
  }
  else
  {
    lcd.setCursor(8, 0);
    lcd.write(7);
  }

  delay(1000);
}
