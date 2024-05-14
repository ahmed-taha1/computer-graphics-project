#include <cstdlib>
#include <GL/glut.h>
using namespace std;

enum Color {WHITE, BROWN, ORANGE, GREY, BLUE, DARK_GREY, YELLOW, GREEN,BLACK};

// translation
float X = 0, Y = 0, Z = 0;
// rotation
float I = 0, J = 0, K = 0;
// scale
float SCALE = 1;

void applyTranslationRotation() {
    glTranslatef(X, Y, Z);
    glRotatef(I, 1, 0, 0);
    glRotatef(J, 0, 1, 0);
    glRotatef(K, 0, 0, 1);
}

void colorFactory(Color c) {
    switch(c) {
        case WHITE:
            glColor3f(0.90, 0.90, 0.90);
            break;
        case BROWN:
            glColor3f(0.45, 0.35, 0.25);
            break;
        case GREY:
            glColor3f(0.8, 0.8, 0.8);
            break;
        case DARK_GREY:
            glColor3f(0.4, 0.4, 0.4);
            break;
        case BLUE:
            glColor3f(0.6, 0.75, 0.85);
            break;
        case ORANGE:
            glColor3f(0.75, 0.25, 0);
            break;
        case YELLOW:
            glColor3f(1, 1, 0);
            break;
        case GREEN:
            glColor3f(0, 0.5, 0);
            break;
        case BLACK:
            glColor3f(0, 0, 0);
            break;
    }
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

    colorFactory(ORANGE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 8);

    lh = l * 0.5;

    GLfloat triangles[] {
            x+lh, y+hh, z,
            x+lh, y-hh, z-bh,
            x+lh, y-hh, z+bh,
            x-lh, y+hh, z,
            x-lh, y-hh, z+bh,
            x-lh, y-hh, z-bh,
    };

    colorFactory(WHITE);
    glVertexPointer(3, GL_FLOAT, 0, triangles);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}



void drawHouse(const float k) {
    // Draw the first floor
    glPushMatrix();
    applyTranslationRotation();
    colorFactory(WHITE);
    drawCube(-0.5 * k, 0, 0, 1 * k);
    drawCube(0.5 * k, 0, 0, 1 * k);

    // Draw door
    colorFactory(BROWN);
    glRotatef(90, 0, k, 0);
    glTranslatef(0, 0, k + 0.01);
    glRectf(-0.15 * k, -0.5 * k, 0.15 * k, 0.1 * k);
    colorFactory(YELLOW);
    glTranslatef(-0.1 * k, -0.2 * k, 0.008);
    glutSolidSphere(0.02f * k, 10, 10);
    glPopMatrix();

    // Draw the black layer between the floors
    glPushMatrix();
    applyTranslationRotation();
    colorFactory(BLACK); // You can adjust the color as needed
    drawCuboid(0, 0.52 * k, 0, 2 * k, 0.04 * k, 1 * k); // Adjust the dimensions of the cuboid
    glPopMatrix();

    // Draw the second floor
    glPushMatrix();
    applyTranslationRotation();
    colorFactory(WHITE);
    drawCube(-0.5 * k, 1.05 * k, 0, 1 * k);
    drawCube(0.5 * k, 1.05 * k, 0, 1 * k);

    // Draw windows
    colorFactory(BLUE); // Assuming blue windows
    float windowWidth = 0.3 * k;
    float windowHeight = 0.3 * k;
    float windowDepth = 0.05 * k;

    // first window
    glPushMatrix();
    glTranslatef(0.35 * k, 1.25 * k, 0.4 * k);
    glRotatef(90, 0, 1, 0); // Rotate the window to face forward
    drawCuboid(0.15*k, 0, 0.65 * k, windowWidth, windowHeight, windowDepth);
    glPopMatrix();

    // Second window
    glPushMatrix();
    glTranslatef(0.35 * k, 1.25 * k, 0.4 * k);
    glRotatef(90, 0, 1, 0); // Rotate the window to face forward
    drawCuboid(0.65*k, 0, 0.65 * k, windowWidth, windowHeight, windowDepth);
    glPopMatrix();

    drawRoof(0, 1.8 * k, 0, 1.2 * k, 2 * k, 0.5 * k);

    glPopMatrix();
}



void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(6, 3, 2, 0, 0, 0, 0, 1, 0);

    drawHouse(SCALE);

    // Draw ground
    colorFactory(GREEN);
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
