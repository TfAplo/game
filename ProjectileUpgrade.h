#ifndef PROJECTILEUPGRADE_H
#define PROJECTILEUPGRADE_H

#include "Upgrades.h"

class ProjectileUpgrade : public Upgrades {
private:
    bool autoAim;
    double speed;
    pair<double,double> position;

public:
    //constructeur
    ProjectileUpgrade(QString name, QString description, QString pathImage,int level, double cooldown, double animationDuration, double dmg, bool autoAim, double speed, pair<double,double> position);

    //methodes
    virtual void defaultAttack(Player& player,vector<Monstre*> monstres);
};

#endif // PROJECTILEUPGRADE_H
