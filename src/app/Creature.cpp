//
// Created by Sveng on 01/01/2026.
//

#include "../../include/Creature.h"
#include <GL/glut.h>
#include <cmath>

Creature::Creature()
    : rotation_(0.0f), animationPhase_(0.0f), legSwing_(20.0f) {}

void Creature::drawBody() {
    glColor3f(0.8f, 0.6f, 0.2f);
    glPushMatrix();
    glScalef(2.0f, 0.6f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Creature::drawLeg(float swingDirection) {
    float angleHip = sinf(animationPhase_) * legSwing_ * swingDirection;
    float angleKnee = 20.0f + sinf(animationPhase_ + 0.5f) * 10.0f;

    glRotatef(angleHip, 1, 0, 0);
    glColor3f(0.7f, 0.2f, 0.2f);
    glPushMatrix();
    glScalef(0.3f, 1.2f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glTranslatef(0, -0.6f, 0);
    glRotatef(-angleKnee, 1, 0, 0);
    glTranslatef(0, -0.6f, 0);

    glColor3f(0.2f, 0.2f, 0.7f);
    glPushMatrix();
    glScalef(0.25f, 1.0f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Creature::draw() {
    glPushMatrix();
    glRotatef(rotation_, 0, 1, 0);
    glTranslatef(0, 0.8f, 0);

    drawBody();

    glPushMatrix();
    glTranslatef(0.8f, -0.3f, 0.5f);
    drawLeg(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8f, -0.3f, -0.5f);
    drawLeg(-1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8f, -0.3f, 0.5f);
    drawLeg(-1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8f, -0.3f, -0.5f);
    drawLeg(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void Creature::update(float deltaTime) {
    animationPhase_ += deltaTime * 5.0f;
}
