#ifndef LEOPARD_H
#define LEOPARD_H

#include "Vec3.h"

class Terrain; // Forward declaration

class Leopard {
public:
    Vec3 position;
    float rotation;
    float animationPhase;
    float moveSpeed;
    float legSwing;

    Leopard();

    void update(float deltaTime, const Terrain* terrain);
    void draw();

    void setKeyState(bool keys[256]);

private:
    bool* keyState;

    void drawBody();
    void drawLeg(float swingDirection);
};

#endif // LEOPARD_H