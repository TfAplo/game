#ifndef BOMBE_H
#define BOMBE_H

#include "objectOnFloor.h"
#include "Player.h"
#include "QTimer"

class bombe : public objectOnFloor
{
private:
    static double rayonExplosion;
    static QString imageIcone;
    QTimer* explosionTimer;
    int level;

public:
    bombe(QGraphicsScene* scene,Player* player, int level);

    virtual void catchObject();
    void explosion(Player* player);

    virtual ~bombe(){}

};

#endif // BOMBE_H
