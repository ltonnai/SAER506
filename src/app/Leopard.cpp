//
// Created by Sveng on 01/01/2026.
//

#include "../../include/Leopard.h"
#include "../../include/Ground.h"
#include <GL/glut.h>
#include <cmath>

Leopard::Leopard() 
    : position(0, 0, 0), rotation(0), animationPhase(0), moveSpeed(5.0f),
      legSwing(20.0f), collisionRadius(1.2f), isSitting(false), sitProgress(0.0f),
      idleTimer(0.0f), keyState(nullptr), isMoving(false), headRotation(0.0f) {}

void Leopard::setKeyState(bool keys[256]) {
    keyState = keys;
}

void Leopard::update(float deltaTime, const Ground* ground) {
    if (keyState == nullptr) return;
    
    // Détermine si le léopard bouge
    isMoving = false;

    // Rotation (Q et D)
    float newRotation = rotation;
    float targetHeadRotation = 0.0f;  // Angle cible pour la tête

    if (keyState['q'] || keyState['Q']) {
        newRotation += 150.0f * deltaTime;
        isMoving = true;
        targetHeadRotation = 25.0f;  // Tourner la tête vers la gauche
    }
    if (keyState['d'] || keyState['D']) {
        newRotation -= 150.0f * deltaTime;
        isMoving = true;
        targetHeadRotation = -25.0f;  // Tourner la tête vers la droite
    }

    // Rotation de la tête
    float headRotationSpeed = 200.0f * deltaTime;
    if (headRotation < targetHeadRotation) {
        headRotation += headRotationSpeed;
        if (headRotation > targetHeadRotation) headRotation = targetHeadRotation;
    } else if (headRotation > targetHeadRotation) {
        headRotation -= headRotationSpeed;
        if (headRotation < targetHeadRotation) headRotation = targetHeadRotation;
    }

    // Vérifier si la rotation cause une collision
    if (ground != nullptr && newRotation != rotation) {
        float newRotRad = newRotation * 3.14159f / 180.0f;
        bool rotationBlocked = false;

        // La tête est en X+ local, la queue en X- local
        float frontX = position.x + cosf(newRotRad) * 1.5f;
        float frontZ = position.z - sinf(newRotRad) * 1.5f;
        float backX = position.x - cosf(newRotRad) * 1.5f;
        float backZ = position.z + sinf(newRotRad) * 1.5f;

        if (ground->checkCollision(frontX, frontZ, 0.5f) ||
            ground->checkCollision(backX, backZ, 0.5f) ||
            ground->checkCollision(position.x, position.z, collisionRadius)) {
            rotationBlocked = true;
        }

        if (!rotationBlocked) {
            rotation = newRotation;
        }
    } else {
        rotation = newRotation;
    }

    Vec3 moveDir(0, 0, 0);

    // La tête du léopard est en X+ local, donc on utilise cos pour X et -sin pour Z
    float radRotation = rotation * 3.14159f / 180.0f;
    if (keyState['z'] || keyState['Z']) {
        moveDir.x += cosf(radRotation);
        moveDir.z -= sinf(radRotation);
        isMoving = true;
    }
    if (keyState['s'] || keyState['S']) {
        moveDir.x -= cosf(radRotation);
        moveDir.z += sinf(radRotation);
        isMoving = true;
    }

    float len = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
    if (len > 0.1f) {
        moveDir.x /= len;
        moveDir.z /= len;

        float newX = position.x + moveDir.x * moveSpeed * deltaTime;
        float newZ = position.z + moveDir.z * moveSpeed * deltaTime;

        if (ground != nullptr) {
            bool inBounds = ground->isInBounds(newX, newZ);
            bool collision = ground->checkCollision(newX, newZ, collisionRadius);

            if (inBounds && !collision) {
                position.x = newX;
                position.z = newZ;
            } else {
                // Essayer de glisser le long des obstacles
                bool xInBounds = ground->isInBounds(newX, position.z);
                bool xCollision = ground->checkCollision(newX, position.z, collisionRadius);
                if (xInBounds && !xCollision) {
                    position.x = newX;
                }

                bool zInBounds = ground->isInBounds(position.x, newZ);
                bool zCollision = ground->checkCollision(position.x, newZ, collisionRadius);
                if (zInBounds && !zCollision) {
                    position.z = newZ;
                }
            }
        } else {
            float halfSize = 24.5f;
            if (newX >= -halfSize && newX <= halfSize) position.x = newX;
            if (newZ >= -halfSize && newZ <= halfSize) position.z = newZ;
        }
    }
    
    // Gestion de l'animation de marche et de l'état assis
    if (isMoving) {
        animationPhase += deltaTime * 5.0f;
        idleTimer = 0.0f;
        isSitting = false;

        if (sitProgress > 0.0f) {
            sitProgress -= deltaTime * 3.0f;
            if (sitProgress < 0.0f) sitProgress = 0.0f;
        }
    } else {
        idleTimer += deltaTime;

        if (idleTimer > 1.5f) {
            isSitting = true;
            if (sitProgress < 1.0f) {
                sitProgress += deltaTime * 2.0f;
                if (sitProgress > 1.0f) sitProgress = 1.0f;
            }
        }
    }
}

void Leopard::drawBody() {
    // Inclinaison du corps quand assis
    float bodyTilt = sitProgress * 15.0f;

    glPushMatrix();
    glRotatef(bodyTilt, 0, 0, 1);

    // Corps du léopard
    glColor3f(0.9f, 0.7f, 0.4f);
    glPushMatrix();
    glScalef(2.2f, 0.7f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Tête
    glColor3f(0.95f, 0.75f, 0.45f);
    glPushMatrix();
    float headLift = sitProgress * 0.2f;
    glTranslatef(1.3f, 0.2f + headLift, 0);
    glRotatef(headRotation, 0, 1, 0);  // Rotation de la tête gauche/droite
    glutSolidSphere(0.4f, 16, 16);
    glPopMatrix();
    
    // Oreille
    glColor3f(0.85f, 0.65f, 0.35f);
    glPushMatrix();
    glTranslatef(1.3f, 0.2f + headLift, 0);  // Position du centre de la tête
    glRotatef(headRotation, 0, 1, 0);  // Rotation avec la tête
    glTranslatef(0.1f, 0.35f, -0.25f);
    glScalef(0.15f, 0.25f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();

    //2eme oreille
    glPushMatrix();
    glTranslatef(1.3f, 0.2f + headLift, 0);
    glRotatef(headRotation, 0, 1, 0);
    glTranslatef(0.1f, 0.35f, 0.25f);
    glScalef(0.15f, 0.25f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Queue
    glColor3f(0.85f, 0.65f, 0.35f);
    glPushMatrix();
    glTranslatef(-1.3f, 0.1f - sitProgress * 0.3f, 0);
    float tailSwing = isSitting ? sinf(animationPhase * 0.5f) * 5.0f : sinf(animationPhase) * 15.0f;
    glRotatef(tailSwing + sitProgress * 30.0f, 0, 1, 0);
    glRotatef(-sitProgress * 20.0f, 0, 0, 1);
    glScalef(0.8f, 0.15f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void Leopard::drawSittingLeg(float swingDirection, bool isFrontLeg) {
    if (isFrontLeg) {
        float angleHip = -10.0f * sitProgress;

        glRotatef(angleHip, 0, 0, 1);
        glColor3f(0.9f, 0.7f, 0.4f);
        glPushMatrix();
        glScalef(0.3f, 1.2f, 0.3f);
        glutSolidCube(1.0f);
        glPopMatrix();

        glTranslatef(0, -0.6f, 0);
        glRotatef(-5.0f, 0, 0, 1);
        glTranslatef(0, -0.6f, 0);

        glColor3f(0.8f, 0.6f, 0.3f);
        glPushMatrix();
        glScalef(0.25f, 1.0f, 0.25f);
        glutSolidCube(1.0f);
        glPopMatrix();
    } else {
        float foldAngle = sitProgress * 70.0f;

        glRotatef(foldAngle, 0, 0, 1);
        glColor3f(0.9f, 0.7f, 0.4f);
        glPushMatrix();
        glScalef(0.3f, 1.2f, 0.3f);
        glutSolidCube(1.0f);
        glPopMatrix();

        glTranslatef(0, -0.6f, 0);
        glRotatef(-90.0f * sitProgress - 20.0f, 0, 0, 1);
        glTranslatef(0, -0.6f, 0);

        glColor3f(0.8f, 0.6f, 0.3f);
        glPushMatrix();
        glScalef(0.25f, 1.0f, 0.25f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
}

void Leopard::drawLeg(float swingDirection) {
    float angleHip = sinf(animationPhase) * legSwing * swingDirection;
    float angleKnee = 20.0f + sinf(animationPhase + 0.5f) * 10.0f;

    glRotatef(angleHip, 0, 0, 1);
    // Cuisse
    glColor3f(0.9f, 0.7f, 0.4f);
    glPushMatrix();
    glScalef(0.3f, 1.2f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glTranslatef(0, -0.6f, 0);
    glRotatef(-angleKnee, 0, 0, 1);
    glTranslatef(0, -0.6f, 0);

    // Tibia
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

    // Ajuster la hauteur quand assis
    float sitHeight = 0.8f - sitProgress * 0.35f;
    glTranslatef(0, sitHeight, 0);

    drawBody();

    if (sitProgress > 0.01f) {
        // Pattes en position assis
        glPushMatrix();
        glTranslatef(0.8f, -0.3f + sitProgress * 0.1f, 0.5f);
        drawSittingLeg(1.0f, true);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.8f, -0.3f + sitProgress * 0.1f, -0.5f);
        drawSittingLeg(-1.0f, true);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.8f, -0.3f + sitProgress * 0.2f, 0.5f);
        drawSittingLeg(-1.0f, false);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.8f, -0.3f + sitProgress * 0.2f, -0.5f);
        drawSittingLeg(1.0f, false);
        glPopMatrix();
    } else {
        // Pattes normale en mouvement
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
    }

    glPopMatrix();
}
