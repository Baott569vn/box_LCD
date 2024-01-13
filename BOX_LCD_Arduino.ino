// Include các thư viện cần thiết
#include "math.h"
#include "Arduino.h"
#include "menuDisplay.h"

// Tạo một thể hiện của lớp menuDisplay
menuDisplay MenuDisplay;

// Định nghĩa một cấu trúc để chứa dữ liệu liên quan đến nút
struct ButtonData
{
  const byte buttonPins[4]; // Pin của các nút
  bool buttonStates[8];     // Theo dõi trạng thái trước đó của các nút
  int binaryTotal;          // Tổng nhị phân của các lần nhấn nút
  byte valueMODE, valueUP, valueDOWN, valueSET;
  bool currentButtonState; // Trạng thái hiện tại của một nút
};

// Tạo một thể hiện của cấu trúc ButtonData và khởi tạo
ButtonData ButtonDataInstance = {
    {3, 4, 5, 6},
    {0, 0, 0, 0, 0, 0, 0, 0},
    0,
    0,
    0,
};

// Hàm setup chạy một lần khi bắt đầu
void setup()
{
  // Bắt đầu giao tiếp serial
  Serial.begin(115200);

  // Đặt chế độ INPUT cho các pin nút
  for (byte i = 3; i <= sizeof(ButtonDataInstance.buttonPins) / sizeof(ButtonDataInstance.buttonPins[0]); ++i)
  {
    pinMode(i, INPUT);
  }

  // Khởi tạo hiển thị menu
  MenuDisplay.begin();
}

// Hàm đọc trạng thái các nút
void readButtonStates()
{
  for (uint8_t index{0}; index < sizeof(ButtonDataInstance.buttonPins) / sizeof(ButtonDataInstance.buttonPins[0]); ++index)
  {
    ButtonDataInstance.currentButtonState = 0;
    ButtonDataInstance.currentButtonState = digitalRead(ButtonDataInstance.buttonPins[index]); // Đọc trạng thái nút nhấn hiện tại

    // Kiểm tra nút có đang giữ không
    ButtonDataInstance.currentButtonState == 1 && ButtonDataInstance.buttonStates[index + 4] == 0 ? ButtonDataInstance.buttonStates[index] = 1 : ButtonDataInstance.buttonStates[index] = 0;

    // Lưu trạng thái hiện tại cho lần kiểm tra tiếp theo
    ButtonDataInstance.buttonStates[index + 4] = ButtonDataInstance.currentButtonState;

    calculateBinaryValue(index);
    // Serial.print(ButtonDataInstance.textButton[index] + String(ButtonDataInstance.buttonStates[index]));
  }
  // Serial.println(String("\tBINARY: ") + ButtonDataInstance.binaryTotal);
  processButtonSelection();
}

// Hàm tính tổng nhị phân của các nút
int calculateBinaryValue(int buttonIndex)
{
  ButtonDataInstance.binaryTotal = (ButtonDataInstance.binaryTotal * 10) + ButtonDataInstance.buttonStates[buttonIndex];
  return ButtonDataInstance.binaryTotal;
}

// Hàm xử lý lựa chọn nút
void processButtonSelection()
{
  switch (ButtonDataInstance.binaryTotal)
  {
  case 1:
    // Serial.println("MODE:");
    ButtonDataInstance.valueMODE += 1;
    ButtonDataInstance.valueMODE > 1 ? ButtonDataInstance.valueMODE = 1 : ButtonDataInstance.valueMODE = ButtonDataInstance.valueMODE;
    MenuDisplay.menuShowAll(1, ButtonDataInstance.valueMODE);
    break;
  case 10:
    // Serial.println("UP:");
    if (ButtonDataInstance.valueMODE == 1)
    {
    }
    ButtonDataInstance.valueUP += 1;
    MenuDisplay.menuShowAll(2, abs(ButtonDataInstance.valueUP));
    ButtonDataInstance.valueUP > MenuDisplay._select_User() ? ButtonDataInstance.valueUP = 1 : ButtonDataInstance.valueUP = ButtonDataInstance.valueUP;
    break;
  case 100:
    // Serial.println("DOWN:");
    if (ButtonDataInstance.valueMODE == 1)
    {
    }
    ButtonDataInstance.valueUP -= 1;
    MenuDisplay.menuShowAll(2, abs(ButtonDataInstance.valueUP));
    ButtonDataInstance.valueUP > MenuDisplay._select_User() ? ButtonDataInstance.valueUP = 1 : ButtonDataInstance.valueUP = ButtonDataInstance.valueUP;
    break;
  case 1000:
    Serial.println("SET:");
    MenuDisplay.menuShowAll(4, 4);
    break;

  default:
    break;
  }
}

// Hàm reset giá trị nhị phân
void resetBinaryValue()
{
  ButtonDataInstance.binaryTotal = 0;
}

// Hàm lặp chính
void loop()
{
  readButtonStates();
  resetBinaryValue();
}
