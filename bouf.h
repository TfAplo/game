#ifndef BOUF_H
#define BOUF_H

#include "objectOnFloor.h"
#include "Player.h"

class bouf : public objectOnFloor
{
private:
    static int soin;
    static QString imageIcone;
    Player* player;
public:
    bouf(QGraphicsScene* scene,Player* player,QPointF position);

    virtual void catchObject();

    virtual ~bouf(){}
};

#endif // BOUF_H
