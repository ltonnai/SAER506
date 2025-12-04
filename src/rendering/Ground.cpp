//
// Created by Sveng on 04/12/2025.
//

#include "GL/freeglut.h"
#include "Ground.h"

Ground::Ground() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(-50.0, 0.0, -50.0);
        glVertex3f(50.0, 0.0, -50.0);
        glVertex3f(50.0, 0.0, 50.0);
        glVertex3f(-50.0, 0.0, 50.0);
    glEnd();

}