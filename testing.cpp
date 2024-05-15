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
float SCALE = 1;

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

void drawDoor(const float k) {
    setDrawingColor(BROWN);
    float doorWidth = 0.4f * k;
    float doorHeight = 0.7f * k;
    float doorDepth = 0.05f * k;

    // Check if the door is open or closed
    if (isDoorClosed) {
//        glRotatef(90, 0, k, 0);
//        glTranslatef(0, 0, k + 0.01f);
//        glRectf(-0.15f * k, -0.5f * k, 0.15f * k, 0.1f * k);
//        setDrawingColor(YELLOW);
//        glTranslatef(-0.1f * k, -0.2f * k, 0.008);
//        glutSolidSphere(0.02f * k, 10, 10);

        // Draw closed door
        glTranslatef(0.35f * k, 1.25f * k, 0.4f * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.4f * k, -1.4f * k, 0.65f * k, doorWidth, doorHeight, doorDepth);
    } else {
        // opened door
        glTranslatef(0.35f * k, 1.25f * k, -0.4f * k);
        glRotatef(45, 0, 1, 0);
        drawCuboid(0.4f * k, -1.4f * k, 0.65f * k, doorWidth, doorHeight, doorDepth);
    }
}

void drawBottomFloor(const float k) {
    setDrawingColor(WHITE);
    drawCuboid(0, 0, 0, 2 * k, 1 * k, 2 * k);
}

void drawSeparator(const float k) {
    applyTranslationRotation();
    setDrawingColor(BLACK);
    drawCuboid(0, 0.52f * k, 0, 2 * k, 0.04f * k, 2 * k);
}

void drawTopWindows(const float k) {
    setDrawingColor(BLUE);
    float windowWidth = 0.4f * k;
    float windowHeight = 0.4f * k;
    float windowDepth = 0.05f * k;

    if (areWindowsClosed) {
        // First window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, 0.4f * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0, 0, 0.65f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // Second window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, 0.4f * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.8f * k, 0, 0.65f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, 0.4f * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.8f * k, 0, -1.4f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // fourth window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, 0.4f * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0 * k, 0, -1.4f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

    } else {
        // first window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, -0.4f * k);
        glRotatef(45, 0, 1, 0);
        drawCuboid(0, 0, 1.2f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // Second window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, -0.4f * k);
        glRotatef(45, 0, 1, 0);
        drawCuboid(0.8f * k, 0, 0.4f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, 0.4f * k);
        glRotatef(125, 0, 1, 0);
        drawCuboid(0.8f * k, 0, -1.3f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // fourth window
        glPushMatrix();
        glTranslatef(0.35f * k, 1.25f * k, -0.4f * k);
        glRotatef(60, 0, 1, 0);
        drawCuboid(-0.8f * k, 0, -1.3f * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();
    }
}

void drawSecondFloor(const float k) {
    setDrawingColor(WHITE);
    drawCuboid(0, 1.05f * k, 0, 2 * k, 1 * k, 2 * k);
    drawTopWindows(k);
}

void drawHouse(const float k) {
    glPushMatrix();
    applyTranslationRotation();
    drawBottomFloor(k);
    drawDoor(k);
    glPopMatrix();

    glPushMatrix();
    drawSeparator(k);
    glPopMatrix();

    glPushMatrix();
    applyTranslationRotation();
    drawSecondFloor(k);

    drawRoof(0, 1.8f * k, 0, 2.0f * k, 2 * k, 0.5f * k);

    glPopMatrix();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
//    gluLookAt(6, 3, 2, 0, 0, 0, 0, 1, 0);
    updateCameraPosition();
    // Look from the new camera position towards the origin
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0, 1, 0);
    drawHouse(SCALE);

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