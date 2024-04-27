#include "aimant.h"
#include "OrbeXP.h"
using namespace std;

QString aimant::imageIcone = QString(":/graphics/Tiles/aimant.png");

aimant::aimant(QGraphicsScene* scene, Player* player,QPointF position) :
    objectOnFloor(position,imageIcone,scene){
    this->player = player;
}

// recuperer toutes les orbes sur la map
void aimant::catchObject(){
    for (auto it = OrbeXP::vecOrbeXP.begin(); it != OrbeXP::vecOrbeXP.end(); ++it) {
        OrbeXP* orbeXP = *it;
        player->ajouterXP(orbeXP->getXP());
        delete orbeXP;
        OrbeXP::vecOrbeXP.erase(it);
        --it;
        }
}
