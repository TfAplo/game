#include "upgradeSpeed.h"

upgradeSpeed::upgradeSpeed(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent)
    : upgradePlayer(name,description,imageIcone,boostValue,parent){}



void upgradeSpeed::defaultAttack(Player& player){
    double pourcentage = static_cast<double>(this->getLevel() * this->getBoostValue()) / 100.0;
    double toAdd = pourcentage * player.getSpeed();
    player.setSpeed(player.getSpeed() + toAdd);

}
