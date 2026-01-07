#include "../../include/Ground.h"
#include <GL/glut.h>

Ground::Ground(float w, float d) : width(w), depth(d) {}

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

