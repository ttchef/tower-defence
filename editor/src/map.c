
#include "map.h"
#include "definies.h"
#include "Manager.h"
#include <wsJson/ws_globals.h>

void updateMapState(Manager* manager) {
    int32_t i = manager->guiWidth;
    i++;
}

void drawMap(Manager* manager) {
    MapState* m = &manager->map;
    m->map.backgroundColor.a = 255;
    
    DrawRectangle(0, 0, manager->mapWidth, manager->mapHeight, m->map.backgroundColor);
}

void drawMapStateGui(Manager* manager) {
    MapState* m = &manager->map;

    const int32_t guiOffset = manager->windowWidth - manager->guiWidth;
    const int32_t paddingX = 15;
    const int32_t paddingY = 15;
    const int32_t widthPadding = manager->guiWidth - paddingX * 2;
    int32_t currentY = paddingY;
    
    DrawRectangle(guiOffset, 0, manager->guiWidth, manager->guiHeight, DARKGRAY);

    GuiColorPicker((Rectangle){guiOffset + paddingX, currentY, widthPadding, widthPadding}, "Background Color", &m->map.backgroundColor);
    currentY += widthPadding;
}

void drawMapState(Manager *manager) {
    drawMap(manager);
    drawMapStateGui(manager);
}

void deinitMapState(Manager *manager) {
    int32_t window = manager->windowHeight;
    window++;
}

// Blueprint json with all values set to null
void createJsonNullObject(wsJson** root) {
    *root = wsJsonInitObject(NULL);
    
    wsJsonAddNull(*root, "name");
}

void newMap(Manager *manager, const char *filepath) {
    MapState* m = &manager->map;

    // Create File
    FILE* file = fopen(filepath, "w");
    if (!file) {
        fprintf(stderr, "Failde to create new Map: %s!\n", filepath);
        return;
    }

    m->filepath = filepath;

    // Create Json
    if (m->json) {
        wsJsonFree(m->json);
    }
    createJsonNullObject(&m->json);

    // print json to file
    char string[WS_BUFFER_SIZE];
    wsJsonToString(m->json, string, WS_BUFFER_SIZE);
    printf("%s\n", string);
    fprintf(file, "%s\n", string);
    fclose(file);
}

