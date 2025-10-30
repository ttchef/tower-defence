
#include "file.h"
#include "Manager.h"
#include <raylib.h>

void updateFileState(Manager *manager) {
    int32_t g = manager->windowHeight;
    g++;
}


void drawFileStateGui(Manager* manager) {
    const int32_t guiOffset = manager->windowWidth - manager->guiWidth;

    DrawRectangle(guiOffset, 0, manager->guiWidth, manager->guiHeight, DARKGRAY);
}

void drawFileState(Manager *manager) {
    drawFileStateGui(manager);
}

