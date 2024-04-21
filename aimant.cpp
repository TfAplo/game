#include "aimant.h"
#include <iostream>
using namespace std;

QString aimant::imageIcone = QString(":/graphics/Tiles/aimant.png");

aimant::aimant(QGraphicsScene* scene, Player* player,QPointF position) :
    objectOnFloor(position,imageIcone,scene){
    this->player = player;
}

void aimant::catchObject(){
    cout << "aimant" << endl;
}
