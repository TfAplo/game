#include "upgradePlayerArmor.h"

QString upgradePlayerArmor::name = QString("Armure");
QString upgradePlayerArmor::description = QString("Augmente la résistance aux dégats");
QString upgradePlayerArmor::imageIcone = QString(":/graphics/UpgradeImages/Armure.png");
int upgradePlayerArmor::valueBoost = 5;

upgradePlayerArmor::upgradePlayerArmor(Player *player)
    : upgradePlayer(name,description,imageIcone,player,valueBoost){
}

void upgradePlayerArmor::effect(){
    player->setArmor(1);
    player->setArmor(player->getArmor() + this->getLevel() * 2);
}
