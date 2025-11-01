
#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "definies.h"

typedef struct MenuBar {
    int32_t height;   
} MenuBar;

void updateMenuBar(Manager* manager);
void drawMenuBar(Manager* manager);

#endif
