#ifndef SAER506_GROUND_H
#define SAER506_GROUND_H

class Ground {
private:
    float width;
    float depth;

public:
    Ground(float w = 25.0f, float d = 25.0f);
    void draw();
};

#endif //SAER506_GROUND_H

