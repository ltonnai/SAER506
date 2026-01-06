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

    glPopMatrix();
}
