
#include "menuBar.h"
#include "Manager.h"

void initMneuBar(Manager *manager) {
    MenuBar* bar = &manager->bar;
    
    // height set? 
    if (bar->height == 0) bar->height = 40;

    bar->paddingXBound = 6;
    bar->paddingYBound = 6;
    bar->paddingXObject = 15;
    bar->currentX = bar->paddingXBound;
    bar->buttonHeight = bar->height - bar->paddingYBound * 2;

    bar->file = (Rectangle){
        bar->currentX,
        bar->paddingYBound,
        80,
        bar->buttonHeight,
    };
    bar->currentX += 20;

}

void updateMenuBar(Manager *manager) {
    int32_t x = manager->windowHeight;
    x++;
}

void drawMenuBar(Manager *manager) {
    MenuBar* bar = &manager->bar;
    DrawRectangle(0, 0, manager->windowWidth, bar->height, DARKGRAY);

    // Draw File
    GuiButton(bar->file, "File");
}

