#ifndef UPGRADEPLAYERCOEUR_H
#define UPGRADEPLAYERCOEUR_H

#include "upgradePlayer.h"
#include "Player.h"

class upgradePlayerCoeur : public upgradePlayer
{

public:
    upgradePlayerCoeur(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent = 0);

    // methodes
    virtual void defaultAttack(Player& player);
};

#endif // UPGRADEPLAYERCOEUR_H
