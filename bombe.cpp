#include "bombe.h"
#include <iostream>
using namespace std;

double bombe::rayonExplosion = 30;
QString bombe::imageIcone = QString(":/graphics/Tiles/bombe_pixel.png");

bombe::bombe(QGraphicsScene* scene, Player* player):
    objectOnFloor(player->pos(),imageIcone,scene){
}

void bombe::catchObject(){
    explosion();
}

void bombe::explosion(){
    cout << "explosion" << endl;
}

