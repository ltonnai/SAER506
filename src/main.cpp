#include <GL/glut.h>
#include "../include/Leopard.h"
#include "../include/Ground.h"

// Global variables
Leopard* g_leopard = nullptr;
Ground* g_ground = nullptr;
int g_lastTime = 0;
bool g_keys[256] = {false};

// ============ OpenGL Functions ============
void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera follows leopard
    float camX = g_leopard->position.x;
    float camY = g_leopard->position.y + 3.5f;
    float camZ = g_leopard->position.z - 6.0f;

    gluLookAt(
        camX, camY, camZ,
        g_leopard->position.x, g_leopard->position.y + 0.5f, g_leopard->position.z,
        0, 1, 0
    );

    g_ground->draw();
    g_leopard->draw();

    // Display controls
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glColor3f(1, 1, 1);
    renderText(10, 30, "W/A/S/D: Move | ESC: Exit");
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

void timer(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - g_lastTime) / 1000.0f;
    g_lastTime = currentTime;

    if (deltaTime > 0.016f) deltaTime = 0.016f;  // Cap deltaTime

    g_leopard->update(deltaTime, g_ground);
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);  // ESC
    g_keys[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    g_keys[key] = false;
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat lightPos[] = {10, 15, 10, 1};
    GLfloat lightAmb[] = {0.3f, 0.3f, 0.3f, 1};
    GLfloat lightDiff[] = {1, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);

    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Leopard Game");

    initGL();

    g_leopard = new Leopard();
    g_ground = new Ground();

    g_leopard->setKeyState(g_keys);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);

    g_lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}