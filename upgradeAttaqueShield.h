#ifndef UPGRADEATTAQUESHIELD_H
#define UPGRADEATTAQUESHIELD_H
#include "upgradeAttaqueMelee.h"

class upgradeAttaqueShield : public upgradeAttaqueMelee
{
private:
    bool actif;
public:
    upgradeAttaqueShield(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,double widthAttaque,double heightAttaque,QGraphicsItem *parent = 0);

    virtual void defaultAttack(Player& player, vector<Monstre*> monstres);
    virtual void affichage(Player& player,upgradeAttaque& upgrade,QGraphicsScene& scene);

};

#endif // UPGRADEATTAQUESHIELD_H
