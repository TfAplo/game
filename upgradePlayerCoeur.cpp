#include "upgradePlayerCoeur.h"

upgradePlayerCoeur::upgradePlayerCoeur(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent)
    : upgradePlayer(name,description,imageIcone,boostValue,parent){}



void upgradePlayerCoeur::defaultAttack(Player& player){
    double pourcentage = static_cast<double>(this->getLevel() * this->getBoostValue()) / 100.0;
    double toAdd = pourcentage * player.getMaxHp();
    player.setMaxHp(player.getMaxHp() + toAdd);
}
