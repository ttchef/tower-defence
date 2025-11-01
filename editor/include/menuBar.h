
#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "definies.h"

typedef struct MenuBar {
    int32_t height;   
    int32_t paddingXBound;
    int32_t paddingYBound;
    int32_t paddingXObject;
    int32_t currentX;
    int32_t buttonHeight;

    Rectangle file;
} MenuBar;

void initMneuBar(Manager* manager);
void updateMenuBar(Manager* manager);
void drawMenuBar(Manager* manager);

#endif
