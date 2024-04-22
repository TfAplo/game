#ifndef UPGRADEATTAQUEARC_H
#define UPGRADEATTAQUEARC_H
#include "upgradeAttaque.h"

#include "Player.h"
#include "Monstre.h"

class upgradeAttaqueArc : public upgradeAttaque
{
private:
    double widthAttaque;// longueur de l'attaque
    double heightAttaque; // largeur de l'attaque
public:
    upgradeAttaqueArc(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,double widthAttaque,double heightAttaque,QGraphicsItem *parent = 0);

    virtual void defaultAttack(Player& player, vector<Monstre*> monstres);
    virtual void affichage(Player& player,upgradeAttaque& upgrade,QGraphicsScene& scene);

    double getWidth() const;
    double getHeight() const;
};

#endif // UPGRADEATTAQUEARC_H
