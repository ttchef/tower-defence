
#include "menuBar.h"
#include "Manager.h"
#include "definies.h"
#include "map.h"

#include <raylib.h>

#include "tinyfiledialogs/tinyfiledialogs.h"

void initMneuBar(Manager *manager) {
    MenuBar* bar = &manager->bar;
    
    // height set? 
    if (bar->height == 0) bar->height = 40;

    bar->paddingXBound = 6;
    bar->paddingYBound = 6;
    bar->paddingXObject = 15;
    bar->currentX = bar->paddingXBound;
    bar->buttonHeight = bar->height - bar->paddingYBound * 2;

    bar->fileMenu.button = (Rectangle){
        .x = bar->currentX,
        .y = bar->paddingYBound,
        .width = 80,
        .height = bar->buttonHeight,
    };

    bar->fileMenu.buttonText = "File";
    
    const char* options[] = {
        "New",
        "Open",
        "Save",
        "Save As",
    };

    memcpy(bar->fileMenu.options, options, sizeof(options));
    bar->fileMenu.optionsCount = ARRAY_COUNT(options);

    bar->currentX += 80 + bar->paddingXObject;
}

void updateMenuBar(Manager *manager) {
    int32_t x = manager->windowHeight;
    x++;
}

void drawMenuBar(Manager *manager) {
    MenuBar* bar = &manager->bar;
    DrawRectangle(0, 0, manager->windowWidth, bar->height, DARKGRAY);

    // Draw File
    drawDropDownMenu(&bar->fileMenu);
    if (bar->fileMenu.pressed) bar->fileMenu.isOpened = !bar->fileMenu.isOpened;
    switch (bar->fileMenu.pressed) {
        case (1 << 0): {
                const char* filepath = tinyfd_saveFileDialog("New Map", "new.json", 0, NULL, NULL);
                if (filepath) {
                    newMap(manager, filepath);
                }
            }
            break;
        case (1 << 1): {
                if (manager->map.json) {
                    // Ask to save map
                    int32_t save = tinyfd_messageBox("Warning", "You have unsaved changes. Do you want to save them?", "yesno", "warning", 1);
                    if (save) saveMap(manager);   
                }

                const char* filepath = tinyfd_openFileDialog("Open Map", "", 0, NULL, NULL, 0);
                if (filepath) {
                    openMap(manager, filepath);    
                }
            }
            break;
        case (1 << 2):
            saveMap(manager);
        case (1 << 3):

            break;
    };
}

void drawDropDownMenu(DropDownMenu *menu) {
    menu->pressed = 0;
    if (GuiButton(menu->button, menu->buttonText)) {
        menu->isOpened = !menu->isOpened;
    }

    if (menu->isOpened) {
        for (int32_t i = 0; i < menu->optionsCount; i++) {
            Rectangle pos = (Rectangle){
                .x = menu->button.x,
                .y = menu->button.y + menu->button.height * (i + 1),
                .width = menu->button.width,
                .height = menu->button.height,
            };
            if (GuiButton(pos, menu->options[i])) {
                int32_t num = 1 << i;
                menu->pressed |= num;
            }
        }
    }
}

