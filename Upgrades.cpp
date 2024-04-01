#include "Upgrades.h"
#include <QString>

using namespace std;

//constructeur
Upgrades::Upgrades(QString name, QString description, QString pathImage,int level,double cooldown,double animationDuration,double dmg) {
    this->name = name;
    this->description = description;
    this->pathImage = pathImage;
    this->level = level;
    this->cooldown = cooldown;
    this->animationDuration = animationDuration;
    this->dmg = dmg;
}

// methode pour incrementer le niveau de l'upgrade
void Upgrades::upgradeLevel(Player& player)
{
    this->level += 1;
}

void Upgrades::defaultAttack(Player& player, vector<Monstre*> monstres){}

// GETTER / SETTER
QString Upgrades::getName() const {
    return this->name;
}

QString Upgrades::getDescription() const {
    return this->description;
}

QString Upgrades::getPathImage() const {
    return this->pathImage;
}

int Upgrades::getLevel() const{
    return this->level;
}

double Upgrades::getCooldown() const {
    return this->cooldown;
}

double Upgrades::getAnimationDuration() const {
    return this->animationDuration;
}
double Upgrades::getDmg() const {
    return this->dmg;
}
