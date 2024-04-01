#ifndef MELEEUPGRADE_H
#define MELEEUPGRADE_H

#include "Upgrades.h"

class MeleeUpgrade : public Upgrades {

private:
    double widthRange;
    double heightRange;

public:
    //constructeur
    MeleeUpgrade(QString name, QString description,QString pathImage, int level, double cooldown, double animationDuration, double dmg, double widthRange, double heightRange);
    //methodes
    virtual void defaultAttack(Player& player,vector<Monstre*> monstres);

};

#endif // MELEEUPGRADE_H
