#include "../../include/Camera.h"
#include <GL/glut.h>
#include <cmath>

Camera::Camera(float dist)
    : distance(dist), angleH(0.0f), angleV(30.0f),
      rotationSpeed(100.0f), minDistance(3.0f), maxDistance(30.0f),
      zoomSpeed(1.5f), keyState(nullptr) {}

void Camera::setKeyState(bool keys[256]) {
    keyState = keys;
}

void Camera::zoomIn() {
    distance -= zoomSpeed;
    if (distance < minDistance) distance = minDistance;
}

void Camera::zoomOut() {
    distance += zoomSpeed;
    if (distance > maxDistance) distance = maxDistance;
}

void Camera::update(float deltaTime) {
    if (keyState == nullptr) return;

    // Touches fleches pour la rotation de la caméra
    if (keyState[100]) { // Flèche gauche
        angleH += rotationSpeed * deltaTime;
    }
    if (keyState[102]) { // Flèche droite
        angleH -= rotationSpeed * deltaTime;
    }
    if (keyState[101]) { // Flèche haut
        angleV -= rotationSpeed * deltaTime;
        if (angleV < 5.0f) angleV = 5.0f; // Limite basse
    }
    if (keyState[103]) { // Flèche bas
        angleV += rotationSpeed * deltaTime;
        if (angleV > 80.0f) angleV = 80.0f; // Limite haute
    }

    // Garder l'angle horizontal entre 0 et 360
    if (angleH > 360.0f) angleH -= 360.0f;
    if (angleH < 0.0f) angleH += 360.0f;
}

void Camera::apply(const Vec3& targetPosition) {
    // Convertir les angles en radians
    float radH = angleH * 3.14159f / 180.0f;
    float radV = angleV * 3.14159f / 180.0f;

    // Calculer la position de la caméra en coordonnées sphériques
    float camX = targetPosition.x + distance * cosf(radV) * sinf(radH);
    float camY = targetPosition.y + distance * sinf(radV);
    float camZ = targetPosition.z + distance * cosf(radV) * cosf(radH);

    // Appliquer la vue
    gluLookAt(camX, camY, camZ,                    // Position de la caméra
              targetPosition.x, targetPosition.y + 0.5f, targetPosition.z,
              0.0f, 1.0f, 0.0f);
}

