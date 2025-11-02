
#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "definies.h"

#define DROPDOWN_MENU_MAX_OPTIONS_COUNT 10

typedef struct DropDownMenu {
    const char* options[DROPDOWN_MENU_MAX_OPTIONS_COUNT];
    int32_t optionsCount;
    bool isOpened;
    Rectangle button;
    const char* buttonText;
    int32_t pressed;
} DropDownMenu;

typedef struct MenuBar {
    int32_t height;   
    int32_t paddingXBound;
    int32_t paddingYBound;
    int32_t paddingXObject;
    int32_t currentX;
    int32_t buttonHeight;

    DropDownMenu fileMenu;
} MenuBar;

void initMneuBar(Manager* manager);
void updateMenuBar(Manager* manager);
void drawMenuBar(Manager* manager);

void drawDropDownMenu(DropDownMenu* menu);


#endif
