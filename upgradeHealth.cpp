#include "upgradeHealth.h"
#include <iostream>
using namespace std;

upgradeHealth::upgradeHealth(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent)
    : upgradePlayer(name,description,imageIcone,boostValue,parent){}



void upgradeHealth::defaultAttack(Player& player){
    double pourcentage = static_cast<double>(this->getLevel() * this->getBoostValue()) / 100.0;
    double toAdd = pourcentage * player.getMaxHp();
    player.setMaxHp(player.getMaxHp() + toAdd);
}
