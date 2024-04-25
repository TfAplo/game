#include "upgradeAttaqueBombes.h"
#include "bombe.h"

QString upgradeAttaqueBombes::name = QString("Bombes");
QString upgradeAttaqueBombes::description = QString("lache des bombes ");
QString upgradeAttaqueBombes::imageIcone = QString(":/graphics/Tiles/bombe_pixel.png");
double upgradeAttaqueBombes::cooldown = 5000;
double upgradeAttaqueBombes::animationDuration = 300;

upgradeAttaqueBombes::upgradeAttaqueBombes(Player *player,QTimer* gameTimer)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone,gameTimer)
{

}


void upgradeAttaqueBombes::effect(){

    bombe* b = new bombe(player->scene(), player, this->getLevel());

}
