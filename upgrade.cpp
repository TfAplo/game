#include "upgrade.h"
//ajout
/*
#include <string>
#include <vector>
#include <iostream>
//fin ajout
*/
#include "upgradeAttaque.h"
#include "upgradePlayer.h"

using namespace std;

Upgrade::Upgrade(QString name,QString description,QString imageIcone,QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    this->name = name;
    this->description = description;
    this->imageIcone = imageIcone;
}

// increment le niveau de l'upgrade par 1
void Upgrade::levelUp(){
    this->level = this->getLevel() + 1;
}




// ---- GETTERS -----

QString Upgrade::getName() const {
    return this->name;
}
QString Upgrade::getDescription() const{
    return this->description;
}
QString Upgrade::getImageIcone() const{
    return this->imageIcone;
}
int Upgrade::getLevel() const{
    return  this->level;
}





//ajout

QString Upgrade::getName() {
    return name;
}

int Upgrade::getNiveau() {
    return level;
}

void Upgrade::setNiveau(int niveau) {
    this->level = niveau;
}

void Upgrade::incrementerNiveau() {
    this->level++;
}
//fin ajout

