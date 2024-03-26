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
    int level;
    double cooldown;

public:
    //constructeur
    Upgrades(QString name, QString description, int level, double cooldown);

    //methodes
    void upgradeLevel(Player& player);
    static void defaultAttack(Player& player,vector<Monstre*> monstres);

};
#endif // UPGRADES_H
