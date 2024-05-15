#ifndef CUBOID_DRAWER_CPP
#define CUBOID_DRAWER_CPP

#include <GL/glut.h>

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

#endif
