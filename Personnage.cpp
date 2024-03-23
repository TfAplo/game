#include "Personnage.h"
#include <iostream>
using namespace std;

Personnage::Personnage(string image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, QGraphicsItem *parent) :
    QObject(), QGraphicsPixmapItem(parent), image(image), position(position), current_hp(current_hp), max_hp(max_hp), speed(speed), dmg(dmg) {}

void Personnage::takeDamage(double dmg)
{
    //verifier qu'on ne descent pas en dessous de 0
    if(this->current_hp - dmg >= 0){
        this->current_hp -= dmg;
    } else {
        // on met a 0
        this->current_hp = 0;
    }
}

void Personnage::attack(Personnage &other)
{
    other.takeDamage(this->dmg);
}

void Personnage::details()
{

    cout << "image : " << this->image << endl;
    cout << "position  x : " << this->position.first << ", y :" << this->position.second << endl;
    cout << "current_hp : " << this->current_hp << endl;
    cout << "max_hp : " << this->max_hp << endl;
    cout << "speed : " << this->speed << endl;
}

