#include <cstdlib>
#include <GL/glut.h>
#include <cmath>

double camX = 6.0f, camY = 3.0f, camZ = 2.0f;
double lookX = 0.0f, lookY = 0.0f, lookZ = 0.0f;

double angleH = 1.5f; // Horizontal angle
double angleV = 0.5f; // Vertical angle
double camDistance = 6.0f; // Distance from the object

void updateCameraPosition() {
    // Calculate camera position using spherical coordinates
    camX = camDistance * sin(angleH) * cos(angleV);
    camY = camDistance * sin(angleV);
    camZ = camDistance * cos(angleH) * cos(angleV);
}

enum Color {WHITE, BROWN, ORANGE, GREY, BLUE, DARK_GREY, YELLOW, GREEN, BLACK};

struct RGBColor {
    float red;
    float green;
    float blue;
};

// Translation
float X = 0, Y = 0, Z = 0;
// Rotation
float I = 0, J = 0, K = 0;

bool isDoorClosed = true;
bool areWindowsClosed = true;


void applyTranslationRotation() {
    glTranslatef(X, Y, Z);
    glRotatef(I, 1, 0, 0);
    glRotatef(J, 0, 1, 0);
    glRotatef(K, 0, 0, 1);
}

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

void drawCube(float x, float y, float z, float length) {

    GLfloat vertices[] = {
            x + length, y + length, z + length,
            x + length, y - length, z + length,
            x - length, y - length, z + length,
            x - length, y + length, z + length,
            x + length, y + length, z - length,
            x + length, y - length, z - length,
            x - length, y - length, z - length,
            x - length, y + length, z - length,
            x - length, y - length, z + length,
            x - length, y + length, z + length,
            x - length, y + length, z - length,
            x - length, y - length, z - length,
            x + length, y - length, z + length,
            x + length, y + length, z + length,
            x + length, y + length, z - length,
            x + length, y - length, z - length,
            x - length, y + length, z + length,
            x - length, y + length, z - length,
            x + length, y + length, z - length,
            x + length, y + length, z + length,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 5 * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawCuboid(float x, float y, float z, float width, float height, float depth) {
    GLfloat vertices[] = {
            // Front face
            x - width / 2, y - height / 2, z + depth / 2,
            x + width / 2, y - height / 2, z + depth / 2,
            x + width / 2, y + height / 2, z + depth / 2,
            x - width / 2, y + height / 2, z + depth / 2,
            // Back face
            x - width / 2, y - height / 2, z - depth / 2,
            x + width / 2, y - height / 2, z - depth / 2,
            x + width / 2, y + height / 2, z - depth / 2,
            x - width / 2, y + height / 2, z - depth / 2,
            // Top face
            x - width / 2, y + height / 2, z + depth / 2,
            x + width / 2, y + height / 2, z + depth / 2,
            x + width / 2, y + height / 2, z - depth / 2,
            x - width / 2, y + height / 2, z - depth / 2,
            // Bottom face
            x - width / 2, y - height / 2, z + depth / 2,
            x + width / 2, y - height / 2, z + depth / 2,
            x + width / 2, y - height / 2, z - depth / 2,
            x - width / 2, y - height / 2, z - depth / 2,
            // Right face
            x + width / 2, y - height / 2, z + depth / 2,
            x + width / 2, y - height / 2, z - depth / 2,
            x + width / 2, y + height / 2, z - depth / 2,
            x + width / 2, y + height / 2, z + depth / 2,
            // Left face
            x - width / 2, y - height / 2, z + depth / 2,
            x - width / 2, y - height / 2, z - depth / 2,
            x - width / 2, y + height / 2, z - depth / 2,
            x - width / 2, y + height / 2, z + depth / 2,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
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

void drawDoor() {
    setDrawingColor(BROWN);
    float doorWidth = 0.4;
    float doorHeight = 0.7;
    float doorDepth = 0.05;

    // Check if the door is open or closed
    if (isDoorClosed) {
        // Draw closed door
        glTranslatef(0.35, 1.25, 0.4);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.4, -1.4, 0.65, doorWidth, doorHeight, doorDepth);
    } else {
        // opened door
        glTranslatef(0.35, 1.25, -0.4);
        glRotatef(45, 0, 1, 0);
        drawCuboid(0.4, -1.4, 0.65, doorWidth, doorHeight, doorDepth);
    }
}

void drawBottomFloor() {
    setDrawingColor(WHITE);
    drawCuboid(0, 0, 0, 2, 1, 2);
}

void drawSeparator() {
    applyTranslationRotation();
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
    applyTranslationRotation();
    drawBottomFloor();
    drawDoor();
    glPopMatrix();

    glPushMatrix();
    drawSeparator();
    glPopMatrix();

    glPushMatrix();
    applyTranslationRotation();
    drawSecondFloor();

    drawRoof(0, 1.8f, 0, 2.0f, 2, 0.5f);

    glPopMatrix();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
//    gluLookAt(6, 3, 2, 0, 0, 0, 0, 1, 0);
    updateCameraPosition();
    // Look from the new camera position towards the origin
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0, 1, 0);
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

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow("House and Bicycle");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}