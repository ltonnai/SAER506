#include "../../include/Ground.h"
#include <GL/glut.h>
#include <cmath>

Ground::Ground(float w, float d) : width(w), depth(d) {
    // Initialiser les obstacles (positions relatives au glTranslatef dans draw)
    // Les obstacles sont positionnés à y = -1.03f dans draw()
    obstacles[0] = {-3.0f, 2.0f, 1.0f};   // Cube rouge
    obstacles[1] = {2.0f, -1.5f, 0.8f};   // Cube vert
    obstacles[2] = {0.0f, 3.0f, 1.2f};    // Cube bleu
}

bool Ground::isInBounds(float x, float z) const {
    float margin = 2.0f;
    return (x >= -width + margin && x <= width - margin &&
            z >= -depth + margin && z <= depth - margin);
}

bool Ground::checkCollision(float x, float z, float radius) const {
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        float obsX = obstacles[i].x;
        float obsZ = obstacles[i].z;
        float halfSize = obstacles[i].size / 2.0f + radius;

        // Collision AABB (Axis-Aligned Bounding Box)
        if (x >= obsX - halfSize && x <= obsX + halfSize &&
            z >= obsZ - halfSize && z <= obsZ + halfSize) {
            return true;
        }
    }
    return false;
}

float Ground::getHalfSize() const {
    return width;  // ou depth, ils sont égaux par défaut
}

void Ground::draw() {
    glPushMatrix();
    glTranslatef(0, -1.03f, 0);

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-width, 0.0f, -depth);
    glVertex3f(width, 0.0f, -depth);
    glVertex3f(width, 0.0f, depth);
    glVertex3f(-width, 0.0f, depth);
    glEnd();

    glPushMatrix();
    glTranslatef(-3.0f, 0.5f, 2.0f);
    glColor3f(0.8f, 0.2f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0f, 0.4f, -1.5f);
    glColor3f(0.2f, 0.7f, 0.3f);
    glutSolidCube(0.8f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 3.0f);
    glColor3f(0.3f, 0.3f, 0.8f);
    glutSolidCube(1.2f);
    glPopMatrix();

    glPopMatrix();
}

