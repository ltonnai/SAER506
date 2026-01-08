#include "../../include/Ground.h"
#include <GL/glut.h>
#include <cmath>

Ground::Ground(float w, float d) : width(w), depth(d) {
    // Initialiser les obstacles (cube)
    obstacles[0] = {-10.0f, 8.0f, 1.5f};    // Cube gris 1
    obstacles[1] = {10.0f, -8.0f, 2.5f};    // Cube gris 2
    obstacles[2] = {0.0f, 12.0f, 2.0f};     // Cube gris 3
    obstacles[3] = {-8.0f, -10.0f, 3.0f};   // Cube gris 4
    obstacles[4] = {14.0f, 4.0f, 1.8f};     // Cube gris 5
    obstacles[5] = {-15.0f, -4.0f, 2.2f};   // Cube gris 6
    obstacles[6] = {6.0f, 10.0f, 2.8f};     // Cube gris 7
    obstacles[7] = {-4.0f, -14.0f, 1.6f};   // Cube gris 8
    obstacles[8] = {12.0f, -12.0f, 2.4f};   // Cube gris 9
    obstacles[9] = {-14.0f, 6.0f, 3.2f};    // Cube gris 10
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

        if (x >= obsX - halfSize && x <= obsX + halfSize &&
            z >= obsZ - halfSize && z <= obsZ + halfSize) {
            return true;
        }
    }
    return false;
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

    // Dessin des cubes (1 à 10)
    glPushMatrix();
    glTranslatef(-10.0f, 0.75f, 8.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(1.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0f, 1.25f, -8.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(2.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 12.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(2.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0f, 1.5f, -10.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(3.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14.0f, 0.9f, 4.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(1.8f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.0f, 1.1f, -4.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(2.2f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.0f, 1.4f, 10.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(2.8f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0f, 0.8f, -14.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(1.6f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12.0f, 1.2f, -12.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(2.4f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.0f, 1.6f, 6.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(3.2f);
    glPopMatrix();

    glPopMatrix();
}

