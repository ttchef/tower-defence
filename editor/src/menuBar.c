
#include "menuBar.h"
#include "Manager.h"

void updateMenuBar(Manager *manager) {
    int32_t x = manager->windowHeight;
    x++;
}

void drawMenuBar(Manager *manager) {
    MenuBar* m = &manager->bar;
    DrawRectangle(0, 0, manager->windowWidth, m->height, DARKGRAY);
}

