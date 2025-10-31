
#include "map.h"
#include "definies.h"
#include "Manager.h"

void updateMapState(Manager *manager) {
    int32_t w = manager->guiHeight;
    w++;
}

void drawMap(Manager* manager) {
    MapState* m = &manager->map;
    m->backgroundColor.a = 255;
    
    DrawRectangle(0, 0, manager->windowWidth - manager->guiWidth, manager->windowHeight, m->backgroundColor);
}

void drawMapStateGui(Manager* manager) {
    MapState* m = &manager->map;

    const int32_t guiOffset = manager->windowWidth - manager->guiWidth;
    const int32_t paddingX = 15;
    const int32_t paddingY = 15;
    const int32_t widthPadding = manager->guiWidth - paddingX * 2;
    int32_t currentY = paddingY;
    
    DrawRectangle(guiOffset, 0, manager->guiWidth, manager->guiHeight, DARKGRAY);

    GuiColorPicker((Rectangle){guiOffset + paddingX, currentY, widthPadding, widthPadding}, "Background Color", &m->backgroundColor);
    currentY += widthPadding;
}

void drawMapState(Manager *manager) {
    drawMap(manager);
    drawMapStateGui(manager);
}

