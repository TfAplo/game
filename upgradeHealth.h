#ifndef UPGRADEHEALTH_H
#define UPGRADEHEALTH_H
#include "upgradePlayer.h"

class upgradeHealth : public upgradePlayer
{
public:
    upgradeHealth(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent = 0);

    // methodes
    virtual void defaultAttack(Player& player);
};

#endif // UPGRADEHEALTH_H
