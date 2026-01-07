#ifndef SAER506_GROUND_H
#define SAER506_GROUND_H

struct Obstacle {
    float x, z;      // Position
    float size;      // Taille du cube
};

class Ground {
private:
    float width;
    float depth;

    static const int NUM_OBSTACLES = 3;
    Obstacle obstacles[NUM_OBSTACLES];

public:
    Ground(float w = 50.0f, float d = 50.0f);
    void draw();

    // Vérifie si une position est dans les limites du terrain
    bool isInBounds(float x, float z) const;

    // Vérifie s'il y a collision avec un obstacle à la position donnée
    bool checkCollision(float x, float z, float radius) const;

    // Retourne la demi-taille du terrain
    float getHalfSize() const;
};

#endif //SAER506_GROUND_H

