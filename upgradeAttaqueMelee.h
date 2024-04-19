#ifndef UPGRADEATTAQUEMELEE_H
#define UPGRADEATTAQUEMELEE_H

#include "upgradeAttaque.h"
#include "Player.h"
#include "Monstre.h"

class upgradeAttaqueMelee : public upgradeAttaque
{
private:
    double widthAttaque;// longueur de l'attaque
    double heightAttaque; // largeur de l'attaque
public:
    upgradeAttaqueMelee(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,double widthAttaque,double heightAttaque,QGraphicsItem *parent = 0);

    virtual void defaultAttack(Player& player, vector<Monstre*> monstres);
    virtual void affichage(Player& player,upgradeAttaque& upgrade,QGraphicsScene& scene);

    double getWidth() const;
    double getHeight() const;
};

#endif // UPGRADEATTAQUEMELEE_H
