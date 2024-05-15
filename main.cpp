#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include "ui_components/cuboid_drawer.cpp"
#include "ui_components/roof_drawer.cpp"
#include "ui_components/door_drawer.cpp"

double camX = 6.0f, camY = 3.0f, camZ = 2.0f;

double angleH = 1.5;
double angleV = 0.5;
double camDistance = 6.0;

bool areWindowsClosed = true;
bool isDoorClosed = true;

void updateCameraPosition() {
    camX = camDistance * sin(angleH) * cos(angleV);
    camY = camDistance * sin(angleV);
    camZ = camDistance * cos(angleH) * cos(angleV);
}


void changeSize(int w, int h) {
    if (h == 0)
        h = 1;
    double ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}




void drawBottomFloor() {
    setDrawingColor(WHITE);
    drawCuboid(0, 0, 0, 2, 1, 2);
}

void drawSeparator() {
    setDrawingColor(BLACK);
    drawCuboid(0, 0.52, 0, 2, 0.04, 2);
}

void drawTopWindows() {
    setDrawingColor(BLUE);
    float windowWidth = 0.4;
    float windowHeight = 0.4;
    float windowDepth = 0.05;

    if (areWindowsClosed) {
        // First window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0, 0, 0.65, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // Second window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.8, 0, 0.65, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.8, 0, -1.4, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // fourth window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0, 0, -1.4, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

    } else {
        // first window
        glPushMatrix();
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(45, 0, 1, 0);
        drawCuboid(0, 0, 1.2, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // Second window
        glPushMatrix();
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(45, 0, 1, 0);
        drawCuboid(0.8, 0, 0.4, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(125, 0, 1, 0);
        drawCuboid(0.8, 0, -1.3, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // fourth window
        glPushMatrix();
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(60, 0, 1, 0);
        drawCuboid(-0.8, 0, -1.3, windowWidth, windowHeight, windowDepth);
        glPopMatrix();
    }
}

void drawSecondFloor() {
    setDrawingColor(WHITE);
    drawCuboid(0, 1.05, 0, 2, 1, 2);
    drawTopWindows();
}

void drawHouse() {
    glPushMatrix();
    drawBottomFloor();
    drawDoor(isDoorClosed);
    glPopMatrix();

    glPushMatrix();
    drawSeparator();
    glPopMatrix();

    glPushMatrix();
    drawSecondFloor();

    drawRoof(0, 1.8f, 0, 2.0f, 2, 0.5f);

    glPopMatrix();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    updateCameraPosition();
    gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
    drawHouse();

    setDrawingColor(GREEN);
    glBegin(GL_QUADS);
    glVertex3f(-5, -0.5, -5);
    glVertex3f(-5, -0.5,  5);
    glVertex3f( 5, -0.5,  5);
    glVertex3f( 5, -0.5, -5);
    glEnd();

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    double zoomThreshold = 0.1f;

    switch (key) {
        case 27:
            exit(0);
        case 'q':
            // Zoom in
        case '+':
            camDistance -= zoomThreshold;
            break;
            // Zoom out
        case '-':
            camDistance += zoomThreshold;
            break;
            // Open door
        case 'o':
            isDoorClosed = false;
            break;
            // Close door
        case 'c':
            isDoorClosed = true;
            break;
            // Open windows
        case 'O':
            areWindowsClosed = false;
            break;
            // Close windows
        case 'C':
            areWindowsClosed = true;
            break;
        default:
            break;
    }
}

void processSpecialKeys(int key, int x, int y) {
    double rotationThreshold = 0.05f;
    double elevationThreshold = 0.05f;

    switch (key) {
        // move camera left
        case GLUT_KEY_LEFT:
            angleH -= rotationThreshold;
            break;
            // move camera right
        case GLUT_KEY_RIGHT:
            angleH += rotationThreshold;
            break;
        case GLUT_KEY_UP:
            angleV += elevationThreshold;
            if (angleV > 1.5f) angleV = 1.5f; // Limit the elevation angle
            break;
        case GLUT_KEY_DOWN:
            angleV -= elevationThreshold;
            if (angleV < -1.5f) angleV = -1.5f; // Limit the elevation angle
            break;
        default:
            break;
    }
}

int main(int argc, char **argv) {
    int w = 1280;
    int h = 720;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow("House and Bicycle");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}