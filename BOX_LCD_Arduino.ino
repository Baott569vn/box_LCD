#include "math.h"
#include "Arduino.h"
#include "menuDisplay.h"

menuDisplay MenuDisplay;

struct data_Button
{
  const byte pinButton[4];
  bool valueButton[8]; // Theo dõi trạng thái trước đó của nút
  // const String textButton[4];
  int BIN_Total;
  bool buttonState;
  byte modeMun;
};

data_Button Data_Button = {{3, 4, 5, 6},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           //  {"BT1: ", "\tBT2: ", "\tBT3: ", "\tBT4: "},
                           0,
                           0,
                           0};

void setup()
{
  Serial.begin(115200);
  for (byte i = 3; i <= sizeof(Data_Button.pinButton) / sizeof(Data_Button.pinButton[0]); ++i)
  {
    pinMode(i, INPUT);
  }
  MenuDisplay.begin();
}

void current_Value_Butt()
{
  for (uint8_t a{0}; a < sizeof(Data_Button.pinButton) / sizeof(Data_Button.pinButton[0]); ++a)
  {
    Data_Button.buttonState = 0;
    Data_Button.buttonState = digitalRead(Data_Button.pinButton[a]);                                                                       // đọc trạng thái nút nhấn hiện tại
    Data_Button.buttonState == 1 && Data_Button.valueButton[a + 4] == 0 ? Data_Button.valueButton[a] = 1 : Data_Button.valueButton[a] = 0; // Kiểm tra nút có đang giữ không
    Data_Button.valueButton[a + 4] = Data_Button.buttonState;                                                                              // Lưu trạng thái hiện tại cho lần kiểm tra tiếp theo

    calculator_Value_Butt(a);
    // Serial.print(Data_Button.textButton[a] + String(Data_Button.valueButton[a]));
  }
  // Serial.println(String("\tBINARY: ") + Data_Button.BIN_Total);
  manualButton();
}

int calculator_Value_Butt(int changMun)
{
  Data_Button.BIN_Total = (Data_Button.BIN_Total * 10) + Data_Button.valueButton[changMun];
  return Data_Button.BIN_Total;
}

void manualButton()
{
  switch (Data_Button.BIN_Total)
  {
  case 1:
    Serial.println("MODE:");
    Data_Button.modeMun += 1;
    MenuDisplay.menuShowAll(1, Data_Button.modeMun);
    Data_Button.modeMun == 4 ? Data_Button.modeMun = 0 : Data_Button.modeMun = Data_Button.modeMun;
    break;
  case 10:
    Serial.println("UP:");
    break;
  case 100:
    Serial.println("DOWN:");
    break;
  case 1000:
    Serial.println("SET:");
    break;

  default:
    break;
  }
}

void resetValueAll()
{
  Data_Button.BIN_Total = 0;
}

void loop()
{
  current_Value_Butt();
  resetValueAll();
}
