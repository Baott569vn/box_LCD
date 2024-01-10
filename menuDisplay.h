#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

class menuDisplay
{
private:
    struct
    {
        String messageLCD[2] = {
            "BAOTT569_SUPER_IOT_HEHE",
            "He_Thong_Kiem_Tra",
        };
        String select_User[4] = {
            "Select: ",
            "MODE> ",
            " <",
            "<SET"};
        byte _munberTheme, selectMode;
    } _LCD_Arduino;

public:
    menuDisplay(byte munberTheme, byte selectMode);
    void begin();
    void menuShow();
};

#endif // MENU_DISPLAY_H