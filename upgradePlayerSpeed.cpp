#include "upgradePlayerSpeed.h"

QString upgradePlayerSpeed::name = QString("Chaussures");
QString upgradePlayerSpeed::description = QString("Augmente votre vitesse de 10%");
QString upgradePlayerSpeed::imageIcone = QString(":/graphics/UpgradeImages/Chaussures.png");
int upgradePlayerSpeed::valueBoost = 10;

upgradePlayerSpeed::upgradePlayerSpeed(Player *player)
    : upgradePlayer(name,description,imageIcone,player,valueBoost)
{

}

void upgradePlayerSpeed::effect(){
    double pourcentage = static_cast<double>(this->getLevel() * valueBoost) / 100.0;
    double toAdd = pourcentage * player->getSpeed();
    player->setSpeed(player->getSpeed() + toAdd);
}
