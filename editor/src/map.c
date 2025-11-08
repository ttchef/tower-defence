
#include "map.h"
#include "definies.h"
#include "Manager.h"
#include "path.h"
#include <raylib.h>
#include <wsJson/ws_globals.h>
#include <wsJson/ws_json.h>

#include <wchar.h>

const char* tabNames[] = {
    "Overall",
    "Path",
    "Textures",
};

char* readFileToString(const char* filename, size_t* size) {
    FILE* file = fileOpen(filename, "rb");
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

void syncMapAndJson(Manager* manager) {
    MapState* m = &manager->map;
    Map* map = &m->map;
    wsJson* root = m->json;

    if (!m->json) return;
    map->backgroundColor.r = wsJsonGetNumber(root, "backgroundColor.red");
    map->backgroundColor.g = wsJsonGetNumber(root, "backgroundColor.green");
    map->backgroundColor.b = wsJsonGetNumber(root, "backgroundColor.blue");

    const char* name = wsJsonGetString(root, "name");
    if (name) {
        strcpy(m->map.name, name);
    }
}

void addEmptyPath(Manager* manager) {
    MapState* m = &manager->map;
    Map* map = &m->map;

    if (!map->paths) {
        map->pathsCount = 1;
        map->paths = malloc(sizeof(Path) * map->pathsCount);
        if (!map->paths) {
            fprintf(stderr, "Failed to allocate path!\n");
            map->pathsCount = 0;
            return;
        }
    }
    else {
        map->pathsCount++;
        map->paths = realloc(map->paths, map->pathsCount);
        if (!map->paths) {
            fprintf(stderr, "Failed to realloc paths!\n");
            exit(-1);
        }
    }
    PathInitEmpty(&map->paths[map->pathsCount - 1]);
}

void addPathWindow(Manager* manager) {
    const int32_t centerX = manager->mapWidth / 2;
    const int32_t centerY = manager->mapHeight / 2;

    // Rectangle in the middle of the screen
    const int32_t backgroundWidth = manager->windowWidth * 0.5;
    const int32_t backgroundHeight = manager->windowHeight * 0.5;
    Rectangle rect = {
        .x = centerX - backgroundWidth / 2,
        .y = centerY - backgroundHeight / 2,
        .width = backgroundWidth,
        .height = backgroundHeight,
    };
    DrawRectangleRounded(rect, 0.1f, 10, DARKGRAY);

    if (GuiButton((Rectangle){centerX, centerY, 100, 20}, "Close")) {
        manager->map.popUps &= ~MAP_STATE_POP_UP_ADD_PATH;
    }
}

void initMapState(Manager *manager) {
    MapState* m = &manager->map;

    // Initial text
    const char* initialText = "Map Name";
    strcpy(m->map.name, initialText);

    for (int32_t i = 0; i < MAP_STATE_TAB_NUM; i++) {
        m->tabs[i] = i;
    }
    m->currentTab = 0;

    m->map.pathsCount = 0;
    m->map.paths = NULL;

    m->followingPoint = -1;
    m->followingPointPath = -1;
}

void updateMapState(Manager* manager) {
    MapState* m = &manager->map;
    Map* map = &m->map;

    // Sync json
    if (m->json) {
        wsJsonSetString(m->json, "name", m->map.name);
        wsJsonSetNumber(m->json, "backgroundColor.red", m->map.backgroundColor.r);
        wsJsonSetNumber(m->json, "backgroundColor.green", m->map.backgroundColor.g);
        wsJsonSetNumber(m->json, "backgroundColor.blue", m->map.backgroundColor.b);
        m->saved = false;
    } 

    if (m->states & MAP_STATE_STATE_CREATE_PATH) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            if (mousePos.x < manager->windowWidth - manager->guiWidth &&
                mousePos.y > manager->windowHeight - manager->mapHeight) {
                Vector2 mousePosWorld = GetScreenToWorld2D(mousePos, manager->camera);

                // Click on point?
                bool endLeftClick = false;
                for (int32_t i = 0; i < map->pathsCount; i++) {
                    Path* path = &map->paths[i];
                    for (int32_t j = 0; j < path->pointsCount; j++) {
                        Vector2* point = &path->points[j];
                        if (mousePosWorld.x > point->x - 7 && mousePosWorld.x < point->x + 7 &&
                            mousePosWorld.y > point->y - 7 && mousePosWorld.y < point->y + 7) {
                            m->followingPointType = PATH_POINT_TYPE_POINT;
                            m->followingPoint = j;
                            m->followingPointPath = i;
                            endLeftClick = true;
                            break;
                        }
                    }
                    for (int32_t j = 0; j < path->controlPointsCount; j++) {
                        Vector2* point = &path->controlPoints[j];
                        if (mousePosWorld.x > point->x - 7 && mousePosWorld.x < point->x + 7 &&
                            mousePosWorld.y > point->y - 7 && mousePosWorld.y < point->y + 7) {
                            m->followingPointType = PATH_POINT_TYPE_CONRTOL_POINT;
                            m->followingPoint = j;
                            m->followingPointPath = i;
                            endLeftClick = true;
                            break;
                        }
                    }
                    if (endLeftClick) break;
                }

                if (!endLeftClick) {
                    PathAddPoint(&m->map.paths[m->map.pathsCount - 1], &mousePosWorld);
                }
            }
        }
    }

    // Deselect following point
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
        m->followingPoint = -1;
        m->followingPointPath = -1;
    }

    if (m->followingPoint != -1 && m->followingPointPath != -1) {
        Path* path = &map->paths[m->followingPointPath];
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), manager->camera);
        if (m->followingPointType == PATH_POINT_TYPE_POINT) {
            path->points[m->followingPoint] = mousePos;
        }
        else if (m->followingPointType == PATH_POINT_TYPE_CONRTOL_POINT) {
            path->controlPoints[m->followingPoint] = mousePos;
        }
    }
}

void drawMap(Manager* manager) {
    MapState* m = &manager->map;
    m->map.backgroundColor.a = 255;
    
    DrawRectangle(0, 0, manager->mapWidth, manager->mapHeight, m->map.backgroundColor);

    // white overlay
    if (m->states & MAP_STATE_STATE_CREATE_PATH) {
        DrawRectangle(0, 0, manager->mapWidth, manager->mapHeight, (Color){255, 255, 255, 100});
    }
    // Path
    for (int32_t i = 0; i < m->map.pathsCount; i++) {
        PathDraw(&m->map.paths[m->map.pathsCount - 1]);
    }
}

void drawMapStateGuiTabOverall(Manager* manager, int32_t guiOffset, int32_t paddingX, int32_t paddingY, int32_t widthPadding, int32_t currentY) {
    MapState* m = &manager->map;
    
    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, 0xffffffff);  
    GuiSetStyle(TEXTBOX, TEXT_COLOR_FOCUSED, 0xffffffff);  
    GuiSetStyle(TEXTBOX, TEXT_COLOR_PRESSED, 0x000000ff);

    static bool textBoxEditMode = false;
    int32_t textHeight = 30;
    if (GuiTextBox((Rectangle){ guiOffset + paddingX, currentY, widthPadding, textHeight}, m->map.name, MAX_MAP_NAME_COUNT, textBoxEditMode)) {
        textBoxEditMode = !textBoxEditMode;
    }
    currentY += textHeight + paddingY;

    GuiColorPicker((Rectangle){guiOffset + paddingX, currentY, widthPadding, widthPadding}, "Background Color", &m->map.backgroundColor);
    currentY += widthPadding;
}

void drawMapStateGuiTabPath(Manager* manager, int32_t guiOffset, int32_t paddingX, int32_t paddingY, int32_t widthPadding, int32_t currentY) {
    MapState* m = &manager->map;
    int32_t y = m->currentTab;
    y++;
    
    int32_t addPointButtonHeight = 30;
    if (GuiButton((Rectangle){guiOffset + paddingX, currentY, widthPadding, addPointButtonHeight}, "Add Path")) {
        addEmptyPath(manager);
        m->states |= MAP_STATE_STATE_CREATE_PATH;
        //m->popUps |= MAP_STATE_POP_UP_ADD_PATH;
    }
    int32_t buttonPadding = 10;  
    currentY += addPointButtonHeight + buttonPadding;

    if (GuiButton((Rectangle){guiOffset + paddingX, currentY, widthPadding, addPointButtonHeight}, "Add Point")) {
    
    }
    currentY += addPointButtonHeight + paddingY;
    
    // Pop ups
    if (m->popUps & MAP_STATE_POP_UP_ADD_PATH) {
        addPathWindow(manager);
    }
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

    const int32_t tabWidth = widthPadding / MAP_STATE_TAB_NUM;
    const int32_t tabHeight = 25;
    for (int32_t i = 0; i < MAP_STATE_TAB_NUM; i++) {
        Rectangle bounds = {
            .x = guiOffset + paddingX + tabWidth * i,
            .y = currentY,
            .width = tabWidth,
            .height = tabHeight,
        };
        if (GuiButton(bounds, tabNames[i])) m->currentTab = i;
    }
    currentY += tabHeight + paddingY;

    switch (m->currentTab) {
        case MAP_STATE_TAB_OVERALL:
            drawMapStateGuiTabOverall(manager, guiOffset, paddingX, paddingY, widthPadding, currentY);
            break;
        case MAP_STATE_TAB_PATH:
            drawMapStateGuiTabPath(manager, guiOffset, paddingX, paddingY, widthPadding, currentY);
            break;
    };
}

void drawMapState(Manager *manager) {
    drawMap(manager);
}

void deinitMapState(Manager *manager) {
    MapState* m = &manager->map;

    if (m->map.paths) free(m->map.paths);
}

// Blueprint json with all values set to null
void createJsonNullObject(wsJson** root) {
    *root = wsJsonInitObject(NULL);
    
    wsJsonAddNull(*root, "name");
    
    wsJson* backgroundColor = wsJsonInitObject("backgroundColor");
    wsJsonAddNull(backgroundColor, "red");
    wsJsonAddNull(backgroundColor, "green");
    wsJsonAddNull(backgroundColor, "blue");
    wsJsonAddField(*root, backgroundColor);

}

void newMap(Manager *manager, const char* filepath) {
    MapState* m = &manager->map;

    // Create File
    FILE* file = fileOpen(filepath, "w");
    if (!file) {
        fprintf(stderr, "Failed to create new Map: %s!\n", filepath);
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

    if (!wsJsonGetString(m->json, "name")) {
        const char* initialText = "Map Name";
        strcpy(m->map.name, initialText);
    }

    m->filepath = filepath;
    syncMapAndJson(manager);
}

void saveMap(Manager* manager) {
    MapState* m = &manager->map;
    if (!m->json) return;

    char string[WS_BUFFER_SIZE];
    wsJsonToString(m->json, string, WS_BUFFER_SIZE);

    FILE* file = fileOpen(m->filepath, "w");
    if (!file) {
        fprintf(stderr, "Failed map: %s to save!\n", m->filepath);
        return;
    }

    fprintf(file, "%s", string);

    fclose(file);
    m->saved = true;
}


