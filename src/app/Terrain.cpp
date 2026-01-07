#include "../../include/Terrain.h"
#include <GL/glut.h>
#include <cmath>

Terrain::Terrain() : gridSize(50), cellSize(1.0f) {}

float Terrain::getHeightAt(float x, float z) const {
    // Utilise la même formule que pour le rendu
    return sinf(x * 0.3f) * 0.1f + cosf(z * 0.3f) * 0.1f;
}

bool Terrain::isInBounds(float x, float z) const {
    float halfSize = gridSize * cellSize / 2.0f;
    float margin = 2.0f; // Petite marge pour éviter de sortir
    return (x >= -halfSize + margin && x <= halfSize - margin &&
            z >= -halfSize + margin && z <= halfSize - margin);
}

float Terrain::getHalfSize() const {
    return gridSize * cellSize / 2.0f;
}

void Terrain::draw() {
    float halfSize = gridSize * cellSize / 2.0f;

    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);

    for (int x = 0; x < gridSize; x++) {
        for (int z = 0; z < gridSize; z++) {
            float x1 = -halfSize + x * cellSize;
            float z1 = -halfSize + z * cellSize;
            float x2 = x1 + cellSize;
            float z2 = z1 + cellSize;

            // Slight height variation
            float y = sinf(x1 * 0.3f) * 0.1f + cosf(z1 * 0.3f) * 0.1f;

            glVertex3f(x1, y, z1);
            glVertex3f(x2, y, z1);
            glVertex3f(x2, y, z2);
            glVertex3f(x1, y, z2);
        }
    }
    glEnd();

    // Grid lines
    glColor3f(0.3f, 0.5f, 0.3f);
    glBegin(GL_LINES);
    for (int i = 0; i <= gridSize; i++) {
        float pos = -halfSize + i * cellSize;
        glVertex3f(pos, 0, -halfSize);
        glVertex3f(pos, 0, halfSize);
        glVertex3f(-halfSize, 0, pos);
        glVertex3f(halfSize, 0, pos);
    }
    glEnd();
}