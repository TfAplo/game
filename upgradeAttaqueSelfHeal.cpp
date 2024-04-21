#include "upgradeAttaqueSelfHeal.h"
#include <iostream>
using namespace std;

QString upgradeAttaqueSelfHeal::name = QString("Serringue");
QString upgradeAttaqueSelfHeal::description = QString("Vous soigne toutes les 10 secondes");
QString upgradeAttaqueSelfHeal::imageIcone = QString(":/graphics/Tiles/tile_0115.png");
double upgradeAttaqueSelfHeal::cooldown = 10000;
double upgradeAttaqueSelfHeal::animationDuration = 0;
double upgradeAttaqueSelfHeal::valueBoost = 10;

upgradeAttaqueSelfHeal::upgradeAttaqueSelfHeal(Player* player) :
    upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone){}


void upgradeAttaqueSelfHeal::effect(){
    // recupere des pv
    double current_hp = player->getCurrent_hp();
    // pourcentage des pv max
    double perc = (valueBoost * this->getLevel() / 100.0) * player->getMaxHp();

    player->heal(current_hp + perc);
}
void upgradeAttaqueSelfHeal::affichage(){

}
