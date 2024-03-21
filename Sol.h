#ifndef SOL_H
#define SOL_H

#include "Terrain.h"

class Sol : public Terrain {
public:
    Sol(const QString& texture, int width, int height, int posX, int posY)
        : Terrain(texture, width, height, posX, posY) {}

};

#endif // SOL_H
