#include "Personnage.h"
#include <iostream>
using namespace std;

void Personnage::takeDamage(double dmg)
{
    //verifier qu'on ne descent pas en dessous de 0
    if(this->current_hp - dmg >= 0.){
        this->current_hp -= dmg;
    } else {
        // on met a 0
        this->current_hp = 0.;
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

void Personnage::keyPressEvent(QKeyEvent *event)
{

}

// crée par raph
QPointF Personnage::getPosition() const {
    return mapToScene(pos());
}

//crée par raph
pair<double,double> Personnage::getPositionPair() const{
    return position;
}

// crée par raph
double Personnage::getCurrent_hp() {
    return current_hp;
}

// crée par raph
void Personnage::setPosition(const pair<double,double> newPosition){
    position = newPosition;
}
