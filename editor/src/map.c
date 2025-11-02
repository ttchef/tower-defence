
#include "map.h"
#include "definies.h"
#include "Manager.h"
#include <wsJson/ws_globals.h>
#include <wsJson/ws_json.h>

char* readFileToString(const char* filename, size_t* size) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int64_t length = ftell(file);
    rewind(file);

    char* buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Failde to alloc memory for buffer when reading a file: %s\n", filename);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, length, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    *size = bytesRead;
    return buffer;
}

void updateMapState(Manager* manager) {
    MapState* m = &manager->map;

    if (!m->json) return;
    wsJson* bgR = wsJsonGet(m->json, "bgR");
    if (bgR->type == WS_JSON_NUMBER) {
        wsJsonSetNumber(m->json, "bgR", m->map.backgroundColor.r);
    }
    else if (bgR->type == WS_JSON_NULL) {
        wsJsonSetNullToNumber(m->json, "bgR", m->map.backgroundColor.r);
    }
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
    int32_t currentY = manager->bar.height;
    
    DrawRectangle(guiOffset, currentY, manager->guiWidth, manager->guiHeight, DARKGRAY);
    currentY += paddingY;

    GuiColorPicker((Rectangle){guiOffset + paddingX, currentY, widthPadding, widthPadding}, "Background Color", &m->map.backgroundColor);
    currentY += widthPadding;
}

void drawMapState(Manager *manager) {
    drawMap(manager);
}

void deinitMapState(Manager *manager) {
    int32_t window = manager->windowHeight;
    window++;
}

// Blueprint json with all values set to null
void createJsonNullObject(wsJson** root) {
    *root = wsJsonInitObject(NULL);
    
    wsJsonAddNull(*root, "name");
    wsJsonAddNull(*root, "bgR");
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
    //printf("%s\n", string);
    fprintf(file, "%s\n", string);
    fclose(file);
}

void openMap(Manager* manager, const char* filepath) {
    MapState* m = &manager->map;
    if (m->json) wsJsonFree(m->json);

    size_t size;
    const char* fileString = readFileToString(filepath, &size);
    if (!fileString) {
        fprintf(stderr, "Failed reading file: %s\n", filepath);
        return;
    }

    m->json = wsStringToJson(&fileString);
    if (!m->json) {
        fprintf(stderr, "Failed to parse file: %s to json\n", filepath);
        return;
    } 
}

void saveMap(Manager* manager) {
    MapState* m = &manager->map;
    if (!m->json) return;

    char string[WS_BUFFER_SIZE];
    wsJsonToString(m->json, string, WS_BUFFER_SIZE);

    FILE* file = fopen(m->filepath, "w");
    if (!file) {
        fprintf(stderr, "Failed to map: %s to save!\n", m->filepath);
        return;
    }

    fprintf(file, "%s", string);

    fclose(file);
}

