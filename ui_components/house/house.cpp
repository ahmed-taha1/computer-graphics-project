#include "house.h"
#include "../cuboid/cuboid.h"
#include "../../colors/colors.h"

#include <GL/glut.h>

void drawDoor(bool isDoorClosed) {
    Colors::setDrawingColor(Color::BROWN);
    float doorWidth = 0.4;
    float doorHeight = 0.7;
    float doorDepth = 0.05;

    if (isDoorClosed) {
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        Cuboid::drawCuboid(0.4, -1.4, 0.65, doorWidth, doorHeight, doorDepth);
    } else {
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(45, 0, 1, 0);
        Cuboid::drawCuboid(0.4, -1.4, 0.65, doorWidth, doorHeight, doorDepth);
    }
}

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
    Colors::setDrawingColor(Color::ORANGE);
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

    Colors::setDrawingColor(Color::WHITE);
    glVertexPointer(3, GL_FLOAT, 0, triangles);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawBottomFloor() {
    Colors::setDrawingColor(Color::WHITE);
    Cuboid::drawCuboid(0, 0, 0, 2, 1, 2);
}

void drawSeparator() {
    Colors::setDrawingColor(Color::BLACK);
    Cuboid::drawCuboid(0, 0.52, 0, 2, 0.04, 2);
}

void drawTopWindows(bool areWindowsClosed) {
    Colors::setDrawingColor(Color::BLUE);
    float windowWidth = 0.4;
    float windowHeight = 0.4;
    float windowDepth = 0.05;

    if (areWindowsClosed) {
        // First window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        Cuboid::drawCuboid(0, 0, 0.65, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // Second window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        Cuboid::drawCuboid(0.8, 0, 0.65, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        Cuboid::drawCuboid(0.8, 0, -1.4, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // fourth window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        Cuboid::drawCuboid(0, 0, -1.4, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

    } else {
        // first window
        glPushMatrix();
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(45, 0, 1, 0);
        Cuboid::drawCuboid(0, 0, 1.2, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // Second window
        glPushMatrix();
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(45, 0, 1, 0);
        Cuboid::drawCuboid(0.8, 0, 0.4, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(125, 0, 1, 0);
        Cuboid::drawCuboid(0.8, 0, -1.3, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // fourth window
        glPushMatrix();
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(60, 0, 1, 0);
        Cuboid::drawCuboid(-0.8, 0, -1.3, windowWidth, windowHeight, windowDepth);
        glPopMatrix();
    }
}

void drawSecondFloor(bool areWindowsClosed) {
    Colors::setDrawingColor(Color::WHITE);
    Cuboid::drawCuboid(0, 1.05, 0, 2, 1, 2);
    drawTopWindows(areWindowsClosed);
}


void House::drawHouse(bool isDoorClosed, bool areWindowsClosed) {
    glPushMatrix();
    drawBottomFloor();
    drawDoor(isDoorClosed);
    glPopMatrix();

    glPushMatrix();
    drawSeparator();
    glPopMatrix();

    glPushMatrix();
    drawSecondFloor(areWindowsClosed);

    drawRoof(0, 1.8f, 0, 2.0f, 2, 0.5f);

    glPopMatrix();
}