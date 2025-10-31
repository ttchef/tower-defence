
#include "file.h"
#include "Manager.h"
#include "map.h"
#include "tinyfiledialogs/tinyfiledialogs.h"

#include <string.h>

void updateFileState(Manager *manager) {
    FileState* f = &manager->file;
    
    if (f->mapOpen || f->newMap) {
        State state = {
            .type = PROGRAM_STATE_MAP,
            .update = updateMapState,
            .draw = drawMapState,
        };
        pushState(manager, state);
    }
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
            manager->file.mapOpen = true;
            strncpy(manager->file.filepath, filename, MAX_FILE_PATH);

            FILE* file = fopen(manager->file.filepath, "r");
            if (!file) {
                fprintf(stderr, "Failed to open map!\n");
                return;
            }
            manager->file.fd = file;
        }
    }

    currentY += mapButtonHeight + paddingY;
    if (GuiButton((Rectangle){guiOffset + paddingX, currentY, 250, mapButtonHeight}, "New Map")) {
        const char* filename = tinyfd_saveFileDialog("New Map", "../../res/maps/new.map", 0, NULL, NULL);
        if (filename) {
            manager->file.newMap = true;
            strncpy(manager->file.filepath, filename, MAX_FILE_PATH);

            // Create File
            FILE* file = fopen(manager->file.filepath, "w");
            if (!file) {
                fprintf(stderr, "Failed to create new map!\n");
                return;
            }
            manager->file.fd = file;
        }
    }

}

void drawFileState(Manager *manager) {
    drawFileStateGui(manager);
}

