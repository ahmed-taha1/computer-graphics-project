#ifndef PROJECT_COLORS_H
#define PROJECT_COLORS_H

enum Color{
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

namespace Colors{
    RGBColor colorFactory(Color c);
    void setDrawingColor(Color color);
}

#endif //PROJECT_COLORS_H
