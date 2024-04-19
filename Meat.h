#ifndef MEAT_H
#define MEAT_H
#include "ObjectOnFloor.h"
#include "Player.h"

class Meat : public ObjectOnFloor
{
public:
    Meat(QString image,pair<int, int> position,QGraphicsItem *parent = 0);

    virtual void catchObject(Player& player);
    virtual ~Meat(){}
};

#endif // MEAT_H
