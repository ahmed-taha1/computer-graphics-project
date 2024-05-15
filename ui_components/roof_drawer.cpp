#ifndef ROOF_DRAWER_CPP
#define ROOF_DRAWER_CPP

#include <GL/glut.h>
#include "../colors.cpp"

void drawRoof(float x, float y, float z, float b, float l, float h) {
    float bh = b * 0.55f;
    float lh = l * 0.55f;
    float hh = h * 0.55f;

    GLfloat vertices[] = {
            x+lh, y+hh, z,
            x+lh, y-hh, z+bh,
            x-lh, y-hh, z+bh,
            x-lh, y+hh, z,
            x+lh, y+hh, z,
            x+lh, y-hh, z-bh,
            x-lh, y-hh, z-bh,
            x-lh, y+hh, z,
    };
    setDrawingColor(ORANGE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 8);

    lh = l * 0.5f;

    GLfloat triangles[] = {
            x+lh, y+hh, z,
            x+lh, y-hh, z-bh,
            x+lh, y-hh, z+bh,
            x-lh, y+hh, z,
            x-lh, y-hh, z+bh,
            x-lh, y-hh, z-bh,
    };

    setDrawingColor(WHITE);
    glVertexPointer(3, GL_FLOAT, 0, triangles);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

#endif
