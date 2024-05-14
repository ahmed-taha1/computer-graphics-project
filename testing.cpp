#include <cstdlib>
#include <GL/glut.h>

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
        case GREY:
            return {0.8, 0.8, 0.8};
        case DARK_GREY:
            return {0.4, 0.4, 0.4};
        case BLUE:
            return {0.6, 0.75, 0.85};
        case ORANGE:
            return {0.75, 0.25, 0};
        case YELLOW:
            return {1, 1, 0};
        case GREEN:
            return {0, 0.5, 0};
        case BLACK:
            return {0, 0, 0};
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
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void drawCube(float x, float y, float z, float length) {
    GLfloat h = length * 0.5f;

    GLfloat vertices[] = {
            x + h, y + h, z + h,
            x + h, y - h, z + h,
            x - h, y - h, z + h,
            x - h, y + h, z + h,
            x + h, y + h, z - h,
            x + h, y - h, z - h,
            x - h, y - h, z - h,
            x - h, y + h, z - h,
            x - h, y - h, z + h,
            x - h, y + h, z + h,
            x - h, y + h, z - h,
            x - h, y - h, z - h,
            x + h, y - h, z + h,
            x + h, y + h, z + h,
            x + h, y + h, z - h,
            x + h, y - h, z - h,
            x - h, y + h, z + h,
            x - h, y + h, z - h,
            x + h, y + h, z - h,
            x + h, y + h, z + h,
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

void drawRoof(float x, float y, float z,
              float b, float l, float h) {

    float bh = b * 0.55;
    float lh = l * 0.55;
    float hh = h * 0.55;

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

    lh = l * 0.5;

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

void drawChimney(const float k) {
    setDrawingColor(GREY);
    drawCube(0.5 * k, 0.65 * k, 0.3 * k, 0.15 * k); // chimney bottom part
    drawCube(0.5 * k, 0.8 * k, 0.3 * k, 0.15 * k); // chimney top part
}

void drawDoor(const float k) {
    setDrawingColor(BROWN);

    // Check if the door is open or closed
    if (isDoorClosed) {
        glRotatef(90, 0, k, 0);
        glTranslatef(0, 0, k + 0.01);
        glRectf(-0.15 * k, -0.5 * k, 0.15 * k, 0.1 * k);
        setDrawingColor(YELLOW);
        glTranslatef(-0.1 * k, -0.2 * k, 0.008);
        glutSolidSphere(0.02f * k, 10, 10);
    } else {
        // Closed door
        glRectf(-0.15 * k, -0.5 * k, 0.15 * k, 0.1 * k);
        setDrawingColor(YELLOW);
        glTranslatef(-0.1 * k, -0.2 * k, 0.008);
        glutSolidSphere(0.02f * k, 10, 10);
    }
}

void drawBottomFloor(const float k) {
    setDrawingColor(WHITE);
    drawCuboid(0, 0, 0, 2 * k, 1 * k, 2 * k);
}

void drawSeparator(const float k) {
    applyTranslationRotation();
    setDrawingColor(BLACK);
    drawCuboid(0, 0.52 * k, 0, 2 * k, 0.04 * k, 2 * k);
}

void drawTopWindows(const float k) {
    setDrawingColor(BLUE);
    float windowWidth = 0.4 * k;
    float windowHeight = 0.4 * k;
    float windowDepth = 0.05 * k;

    if (areWindowsClosed) {
        // First window
        glPushMatrix();
        glTranslatef(0.35 * k, 1.25 * k, 0.4 * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0 * k, 0, 0.65 * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // Second window
        glPushMatrix();
        glTranslatef(0.35 * k, 1.25 * k, 0.4 * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.8 * k, 0, 0.65 * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35 * k, 1.25 * k, 0.4 * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0.8 * k, 0, -1.4 * k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

        // third window
        glPushMatrix();
        glTranslatef(0.35 * k, 1.25 * k, 0.4 * k);
        glRotatef(90, 0, 1, 0);
        drawCuboid(0 * k, 0, -1.4* k, windowWidth, windowHeight, windowDepth);
        glPopMatrix();

    } else {
        // Closed windows
        // Draw closed windows or any other design when windows are closed
    }
}

void drawSecondFloor(const float k) {
    setDrawingColor(WHITE);
    drawCuboid(0, 1.05 * k, 0, 2 * k, 1 * k, 2 * k);
    drawTopWindows(k);
}

void drawHouse(const float k) {
    glPushMatrix();
    applyTranslationRotation();
    drawBottomFloor(k);
    drawChimney(k);
    drawDoor(k);
    glPopMatrix();

    glPushMatrix();
    drawSeparator(k);
    glPopMatrix();

    glPushMatrix();
    applyTranslationRotation();
    drawSecondFloor(k);

    drawRoof(0, 1.8 * k, 0, 2.0 * k, 2 * k, 0.5 * k);

    glPopMatrix();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(6, 3, 2, 0, 0, 0, 0, 1, 0);

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
    float threshold = 0.1;
    switch (key) {
        case 'q':
        case 27:
            exit(0);
            break;
        case 'h':
            Z += threshold;
            break;
        case 'l':
            Z -= threshold;
            break;
        case 'k':
            X -= threshold;
            break;
        case 'j':
            X += threshold;
            break;
        case 'K':
            Y += threshold;
            break;
        case 'J':
            Y -= threshold;
            break;
        case '+':
            SCALE += threshold;
            break;
        case '-':
            if (SCALE > threshold)
                SCALE -= threshold;
            break;
        case 'o':
            isDoorClosed = !isDoorClosed;
            areWindowsClosed = !areWindowsClosed;
            break;
    }
}

void processSpecialKeys(int key, int x, int y) {
    float threshold = 7.5;

    if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) {
        switch (key) {
            case GLUT_KEY_LEFT:
                I += threshold;
                break;
            case GLUT_KEY_RIGHT:
                I -= threshold;
                break;
        }
        return;
    }

    switch (key) {
        case GLUT_KEY_LEFT:
            J -= threshold;
            break;
        case GLUT_KEY_RIGHT:
            J += threshold;
            break;
        case GLUT_KEY_UP:
            K += threshold;
            break;
        case GLUT_KEY_DOWN:
            K -= threshold;
            break;
        case 'w':
            areWindowsClosed = !areWindowsClosed;
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
    glutCreateWindow("3D House");

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
