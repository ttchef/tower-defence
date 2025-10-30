
#include "file.h"
#include "Manager.h"

void updateFileState(Manager *manager) {
    int32_t g = manager->windowHeight;
    g++;
}


void drawFileStateGui(Manager* manager) {
    const int32_t guiOffset = manager->windowWidth - manager->guiWidth;
    const int32_t paddingX = 15;
    const int32_t paddingY = 15;
    int32_t currentY = paddingY;

    DrawRectangle(guiOffset, 0, manager->guiWidth, manager->guiHeight, DARKGRAY);

    int32_t mapButtonHeight = 50;
    GuiButton((Rectangle){guiOffset + paddingX, currentY, 250, mapButtonHeight}, "Open Map");
    currentY += mapButtonHeight + paddingY;
    GuiButton((Rectangle){guiOffset + paddingX, currentY, 250, mapButtonHeight}, "New Map");

}

void drawFileState(Manager *manager) {
    drawFileStateGui(manager);
}

