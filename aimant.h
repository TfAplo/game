#ifndef AIMANT_H
#define AIMANT_H

#include "objectOnFloor.h"
#include "Player.h"

class aimant : public objectOnFloor
{
private:
    static QString imageIcone;
    Player* player;
public:
    aimant(QGraphicsScene* scene, Player* player,QPointF position);

    virtual void catchObject();
    virtual ~aimant(){}
};

#endif // AIMANT_H
