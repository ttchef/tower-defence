
#include "file.h"
#include "Manager.h"
#include "tinyfiledialogs/tinyfiledialogs.h"

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

    if (GuiButton((Rectangle){guiOffset + paddingX, currentY, 250, mapButtonHeight}, "Open Map")) {
        const char* filename = tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 0);
        if (filename) {
            printf("File: %s\n", filename);
        }
    }

    currentY += mapButtonHeight + paddingY;
    if (GuiButton((Rectangle){guiOffset + paddingX, currentY, 250, mapButtonHeight}, "New Map")) {
        const char* filename = tinyfd_saveFileDialog("New Map", "../../res/maps/new.map", 0, NULL, NULL);
        if (filename) {
            printf("File: %s\n", filename);
        }
    }

}

void drawFileState(Manager *manager) {
    drawFileStateGui(manager);
}

