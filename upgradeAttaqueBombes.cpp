#include "upgradeAttaqueBombes.h"
#include "bombe.h"
#include <iostream>
using namespace std;

QString upgradeAttaqueBombes::name = QString("Bombes");
QString upgradeAttaqueBombes::description = QString("lache des bombes ");
QString upgradeAttaqueBombes::imageIcone = QString(":/graphics/Tiles/bombe_pixel.png");
double upgradeAttaqueBombes::cooldown = 2000;
double upgradeAttaqueBombes::animationDuration = 300;

upgradeAttaqueBombes::upgradeAttaqueBombes(Player *player)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone)
{
    this->setActif();
}


void upgradeAttaqueBombes::effect(){

    bombe* b = new bombe(player->scene(), player, this->getLevel());

}
