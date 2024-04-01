#ifndef UPGRADES_H
#define UPGRADES_H
#include <QString>
#include "Player.h"
#include "Monstre.h"

class Upgrades
{
private:
    QString name;
    QString description;
    QString pathImage;
    int level;
    double cooldown;
    double animationDuration;
    double dmg;

public:
    //constructeur
    Upgrades(QString name, QString description,QString pahtImage, int level, double cooldown, double animationDuration,double dmg);

    //methodes
    void upgradeLevel(Player& player);
    //getter / setter
    QString getName() const;
    QString getDescription() const;
    QString getPathImage() const;
    int getLevel() const;
    double getCooldown() const;
    double getAnimationDuration() const;
    double getDmg() const;

    virtual void defaultAttack(Player& player, vector<Monstre*> monstres);

};
#endif // UPGRADES_H
