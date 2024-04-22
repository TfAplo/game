#include "Meat.h"
#include <iostream>
using namespace std;

Meat::Meat(QString image,pair<int, int> position,QGraphicsItem *parent)
    : ObjectOnFloor(image,position,parent){}


// redonne de la vie au joueur
void Meat::catchObject(Player& player){
    cout << "miam" << endl;
    player.setCurrentHp(player.getCurrent_hp() + 50);

}
