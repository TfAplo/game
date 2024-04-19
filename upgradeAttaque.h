#ifndef UPGRADEATTAQUE_H
#define UPGRADEATTAQUE_H
#include "upgrade.h"
#include "Player.h"
#include "Monstre.h"

class upgradeAttaque : public Upgrade
{
private:

    double cooldown; // duree de rechargement de l'attaque
    double animationDuration; //duree animation
    QString imageAnimation; // image utiliser pour l'animation

public:

    upgradeAttaque(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,QGraphicsItem *parent = 0);


    virtual void defaultAttack(Player& player, vector<Monstre*> monstres) = 0;
    virtual void affichage(Player& player,upgradeAttaque& upgrade,QGraphicsScene& scene) = 0;

    double getCooldown() const;
    double getAnimationDuration() const;
    QString getImageAnimation() const;
};

#endif // UPGRADEATTAQUE_H
