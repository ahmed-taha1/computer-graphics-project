#ifndef COLOR_CPP
#define COLOR_CPP

#include <GL/glut.h>

enum Color {
    WHITE,
    BROWN,
    ORANGE,
    GREY,
    BLUE,
    DARK_GREY,
    YELLOW,
    GREEN,
    BLACK
};

struct RGBColor {
    float red;
    float green;
    float blue;
};


RGBColor colorFactory(Color c) {
    switch(c) {
        case WHITE:
            return {0.90, 0.90, 0.90};
        case BROWN:
            return {0.45, 0.35, 0.25};
        case ORANGE:
            return {0.75, 0.25, 0};
        case GREY:
            return {0.8, 0.8, 0.8};
        case DARK_GREY:
            return {0.4, 0.4, 0.4};
        case BLUE:
            return {0.6, 0.75, 0.85};
        case YELLOW:
            return {1, 1, 0};
        case GREEN:
            return {0, 0.5, 0};
        case BLACK:
        default:
            return {0, 0, 0};
    }
}


void setDrawingColor(Color color) {
    RGBColor drawingColor = colorFactory(color);
    glColor3f(drawingColor.red, drawingColor.green, drawingColor.blue);
}


#endif