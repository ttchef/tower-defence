
#include "map.h"
#include "definies.h"
#include "Manager.h"

void updateMapState(Manager *manager) {
    int32_t w = manager->guiHeight;
    w++;
}

void drawMapStateGui(Manager* manager) {
    const int32_t guiOffset = manager->windowWidth - manager->guiWidth;
    //const int32_t paddingX = 15;
    //const int32_t paddingY = 15;
    //int32_t currentY = paddingY;

    DrawRectangle(guiOffset, 0, manager->guiWidth, manager->guiHeight, DARKGRAY);


}

void drawMapState(Manager *manager) {
    drawMapStateGui(manager);
}

