#include "Personnage.h"
#include <iostream>
#include "damageindicator.h"
using namespace std;

QString Personnage::getImage() const
{
    return image;
}

double Personnage::getMax_hp() const
{
    return max_hp;
}

double Personnage::getDmg() const
{
    return dmg;
}

Personnage::Personnage(const QString& image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg,QGraphicsItem *parent) :
    QObject(), QGraphicsPixmapItem(parent), image(image), position(position), current_hp(current_hp), max_hp(max_hp), speed(speed), dmg(dmg), armor(0) {}

void Personnage::takeDamage(double dmg)
{
    if(dmg - this->armor > 0){
        double current_damage = dmg - this->armor;
        //verifier qu'on ne descent pas en dessous de 0
        if(this->current_hp  - current_damage  >= 0.){
            this->current_hp -= current_damage;
        } else {
            // on met a 0
            this->current_hp = 0.;
        }

        DamageIndicator *indic = new DamageIndicator(pos().x(),pos().y(),current_damage);
        scene()->addItem(indic);
    }else{
        DamageIndicator *indic = new DamageIndicator(pos().x(),pos().y(),0);
        scene()->addItem(indic);
    }
}

void Personnage::attack(Personnage &other)
{
    other.takeDamage(this->dmg);
}

void Personnage::details()
{

    cout << "image : " << this->image.toStdString() << endl;
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

//ajout
pair<double, double> Personnage::getPos(){
    return this->position;
}

//ajout par bastien
double Personnage::getArmor(){
    return this->armor;
}

void Personnage::setArmor(double armor){
    this->armor = armor;
}

//fin ajout



