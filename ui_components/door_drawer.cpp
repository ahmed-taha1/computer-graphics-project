#ifndef DOOR_DRAWER_CPP
#define DOOR_DRAWER_CPP

#include "../colors.cpp"
#include "cuboid_drawer.cpp"


void drawDoor(bool isDoorClosed) {
    setDrawingColor(BROWN);
    float doorWidth = 0.4;
    float doorHeight = 0.7;
    float doorDepth = 0.05;

    if (isDoorClosed) {
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.4, -1.4, 0.65, doorWidth, doorHeight, doorDepth);
    } else {
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(45, 0, 1, 0);
        drawCuboid(0.4, -1.4, 0.65, doorWidth, doorHeight, doorDepth);
    }
}
#endif
