#include "../include/Creature.h"
#include <GL/glut.h>

Creature creature;
int lastTime = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(0, 3, 8,   // Caméra
              0, 0, 0,   // Regarde vers
              0, 1, 0);  // Haut
    
    creature.draw();
    
    glutSwapBuffers();
}

void timer(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    
    creature.update(deltaTime);
    creature.setRotation(creature.getRotation() + deltaTime * 10.0f);
    
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat lightPos[] = { 5, 10, 5, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Creature Test");
    
    initGL();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}