#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain {
public:
    Terrain();

    void draw();

    // Retourne la hauteur du terrain à la position (x, z)
    float getHeightAt(float x, float z) const;

    // Vérifie si une position est dans les limites du terrain
    bool isInBounds(float x, float z) const;

    // Retourne la demi-taille du terrain
    float getHalfSize() const;

private:
    int gridSize;
    float cellSize;
};

#endif // TERRAIN_H