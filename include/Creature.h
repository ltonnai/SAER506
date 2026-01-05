//
// Created by Sveng on 01/01/2026.
//

#ifndef SAER506_CREATURE_H
#define SAER506_CREATURE_H

class Creature {
public:
    Creature();

    void draw();
    void update(float deltaTime);

    void setRotation(float angle) { rotation_ = angle; }
    float getRotation() const { return rotation_; }

private:
    void drawBody();
    void drawLeg(float swingDirection);

    float rotation_;
    float animationPhase_;
    float legSwing_;

};

#endif //SAER506_CREATURE_H