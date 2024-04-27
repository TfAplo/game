#include "upgradePlayerHealth.h"
#include <iostream>

QString upgradePlayerHealth::name = QString("Coeur");
QString upgradePlayerHealth::description = QString("Augmente votre vie maximum");
QString upgradePlayerHealth::imageIcone = QString(":/graphics/UpgradeImages/Coeur.png");
int upgradePlayerHealth::valueBoost = 10;

upgradePlayerHealth::upgradePlayerHealth(Player *player)
    : upgradePlayer(name,description,imageIcone,player,valueBoost)
{

}

void upgradePlayerHealth::effect(){
    double pourcentage = static_cast<double>(this->getLevel() * this->valueBoost) / 100.0;
    double toAdd = pourcentage * player->getMaxHp();
    player->setMaxHp(player->getMaxHp() + toAdd);
}
