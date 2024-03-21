#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Terrain.h"

class Obstacle : public Terrain {
public:
    Obstacle(const QString& texture, int width, int height, int posX, int posY)
        : Terrain(texture, width, height, posX, posY) {}

    void afficher();
};

#endif // OBSTACLE_H
