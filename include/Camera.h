#ifndef SAER506_CAMERA_H
#define SAER506_CAMERA_H

#include "Vec3.h"

class Camera {
private:
    float distance;      // Distance de la caméra au léopard
    float angleH;        // Angle horizontal (rotation autour du léopard)
    float angleV;        // Angle vertical (hauteur de la caméra)
    float rotationSpeed; // Vitesse de rotation

    float minDistance;   // Distance minimale (zoom max)
    float maxDistance;   // Distance maximale (dézoom max)
    float zoomSpeed;     // Vitesse du zoom

    bool* keyState;      // État des touches spéciales (flèches)

public:
    Camera(float dist = 10.0f);

    void setKeyState(bool keys[256]);
    void update(float deltaTime);
    void apply(const Vec3& targetPosition);

    // Zoom avec la molette
    void zoomIn();
    void zoomOut();

    // Getters
    float getAngleH() const { return angleH; }
    float getAngleV() const { return angleV; }
    float getDistance() const { return distance; }
};

#endif //SAER506_CAMERA_H

