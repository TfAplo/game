#ifndef BOMBE_H
#define BOMBE_H

#include "objectOnFloor.h"
#include "Player.h"

class bombe : public objectOnFloor
{
private:
    static double rayonExplosion;
    static QString imageIcone;

public:
    bombe(QGraphicsScene* scene,Player* player);

    virtual void catchObject();
    void explosion();

    virtual ~bombe(){}

};

#endif // BOMBE_H
