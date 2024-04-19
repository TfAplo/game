#ifndef UPGRADESPEED_H
#define UPGRADESPEED_H
#include "upgradePlayer.h"
#include "Player.h"

class upgradeSpeed : public upgradePlayer
{

public:
    upgradeSpeed(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent = 0);

    // methodes
    virtual void defaultAttack(Player& player);
};

#endif // UPGRADESPEED_H
