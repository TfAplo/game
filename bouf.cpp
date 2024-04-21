#include "bouf.h"
#include <iostream>
using namespace std;

QString bouf::imageIcone = QString(":/graphics/Tiles/meat_pixel.png");
int bouf::soin = 30;

bouf::bouf(QGraphicsScene* scene, Player* player, QPointF position):
    objectOnFloor(position,imageIcone,scene){
    this->player = player;
}


void bouf::catchObject(){
    // recupere des pv
    double current_hp = player->getCurrent_hp();
    player->heal(current_hp + soin);
}
