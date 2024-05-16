#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include "ui_components/house/house.h"
#include "colors/colors.h"

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




void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    updateCameraPosition();
    gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);

    House::drawHouse(isDoorClosed, areWindowsClosed);

    Colors::setDrawingColor(Color::GREEN);
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









