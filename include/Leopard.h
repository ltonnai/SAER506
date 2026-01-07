#ifndef LEOPARD_H
#define LEOPARD_H

#include "Vec3.h"

class Ground; // Forward declaration

class Leopard {
public:
    Vec3 position;
    float rotation;
    float animationPhase;
    float moveSpeed;
    float legSwing;
    float collisionRadius;  // Rayon de collision du léopard

    // État assis
    bool isSitting;
    float sitProgress;      // 0.0 = debout, 1.0 = assis
    float idleTimer;        // Temps d'immobilité avant de s'asseoir

    // Rotation de la tête
    float headRotation;     // Angle de rotation de la tête (gauche/droite)

    Leopard();

    void update(float deltaTime, const Ground* ground);
    void draw();

    void setKeyState(bool keys[256]);

private:
    bool* keyState;
    bool isMoving;          // Si le léopard bouge actuellement

    void drawBody();
    void drawLeg(float swingDirection);
    void drawSittingLeg(float swingDirection, bool isFrontLeg);
};

#endif // LEOPARD_H