//
// Created by Sveng on 01/01/2026.
//

#include "../../include/Leopard.h"
#include "../../include/Terrain.h"
#include <GL/glut.h>
#include <cmath>

Leopard::Leopard() 
    : position(0, 0, 0), rotation(0), animationPhase(0), moveSpeed(5.0f),
      legSwing(20.0f), keyState(nullptr) {}

void Leopard::setKeyState(bool keys[256]) {
    keyState = keys;
}

void Leopard::update(float deltaTime, const Terrain* terrain) {
    if (keyState == nullptr) return;
    
    animationPhase += deltaTime * 5.0f;

    Vec3 moveDir(0, 0, 0);
    
    // Keyboard controls
    if (keyState['w'] || keyState['W']) {
        moveDir.x += cosf(rotation * 3.14159f / 180.0f);
        moveDir.z += sinf(rotation * 3.14159f / 180.0f);
    }
    if (keyState['s'] || keyState['S']) {
        moveDir.x -= cosf(rotation * 3.14159f / 180.0f);
        moveDir.z -= sinf(rotation * 3.14159f / 180.0f);
    }
    if (keyState['a'] || keyState['A']) {
        rotation += 150.0f * deltaTime;
    }
    if (keyState['d'] || keyState['D']) {
        rotation -= 150.0f * deltaTime;
    }
    
    // Normalize and apply movement
    float len = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
    if (len > 0.1f) {
        moveDir.x /= len;
        moveDir.z /= len;

        // Calculate new position
        float newX = position.x + moveDir.x * moveSpeed * deltaTime;
        float newZ = position.z + moveDir.z * moveSpeed * deltaTime;

        // Vérifier les limites du terrain avant d'appliquer le mouvement
        if (terrain != nullptr && terrain->isInBounds(newX, newZ)) {
            position.x = newX;
            position.z = newZ;
        } else {
            // Fallback: utiliser les anciennes limites si pas de terrain
            float halfSize = 24.5f;
            if (newX >= -halfSize && newX <= halfSize) position.x = newX;
            if (newZ >= -halfSize && newZ <= halfSize) position.z = newZ;
        }
    }
    
    // Ajuster la position Y pour suivre le terrain
    if (terrain != nullptr) {
        position.y = terrain->getHeightAt(position.x, position.z);
    }
}

void Leopard::drawBody() {
    // Corps du léopard - couleur jaune/orange tachetée
    glColor3f(0.9f, 0.7f, 0.4f);
    glPushMatrix();
    glScalef(2.2f, 0.7f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Tête
    glColor3f(0.95f, 0.75f, 0.45f);
    glPushMatrix();
    glTranslatef(1.3f, 0.2f, 0);
    glutSolidSphere(0.4f, 16, 16);
    glPopMatrix();
    
    // Oreilles
    glColor3f(0.85f, 0.65f, 0.35f);
    glPushMatrix();
    glTranslatef(1.4f, 0.55f, -0.25f);
    glScalef(0.15f, 0.25f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.4f, 0.55f, 0.25f);
    glScalef(0.15f, 0.25f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Queue
    glColor3f(0.85f, 0.65f, 0.35f);
    glPushMatrix();
    glTranslatef(-1.3f, 0.1f, 0);
    glRotatef(sinf(animationPhase) * 15.0f, 0, 0, 1);
    glScalef(0.8f, 0.15f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Leopard::drawLeg(float swingDirection) {
    float angleHip = sinf(animationPhase) * legSwing * swingDirection;
    float angleKnee = 20.0f + sinf(animationPhase + 0.5f) * 10.0f;

    glRotatef(angleHip, 0, 0, 1);
    // Cuisse - couleur léopard
    glColor3f(0.9f, 0.7f, 0.4f);
    glPushMatrix();
    glScalef(0.3f, 1.2f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glTranslatef(0, -0.6f, 0);
    glRotatef(-angleKnee, 0, 0, 1);
    glTranslatef(0, -0.6f, 0);

    // Tibia - couleur légèrement plus foncée
    glColor3f(0.8f, 0.6f, 0.3f);
    glPushMatrix();
    glScalef(0.25f, 1.0f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Leopard::draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation, 0, 1, 0);
    glTranslatef(0, 0.8f, 0);

    drawBody();

    // Patte avant droite
    glPushMatrix();
    glTranslatef(0.8f, -0.3f, 0.5f);
    drawLeg(1.0f);
    glPopMatrix();

    // Patte avant gauche
    glPushMatrix();
    glTranslatef(0.8f, -0.3f, -0.5f);
    drawLeg(-1.0f);
    glPopMatrix();

    // Patte arrière droite
    glPushMatrix();
    glTranslatef(-0.8f, -0.3f, 0.5f);
    drawLeg(-1.0f);
    glPopMatrix();

    // Patte arrière gauche
    glPushMatrix();
    glTranslatef(-0.8f, -0.3f, -0.5f);
    drawLeg(1.0f);
    glPopMatrix();

    glPopMatrix();
}
