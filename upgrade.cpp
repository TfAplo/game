#include "upgrade.h"
using namespace std;

Upgrade::Upgrade(QString name,QString description,QString imageIcone,Player* player,QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    this->name = name;
    this->description = description;
    this->imageIcone = imageIcone;
    this->player = player;
    this->level = 1;
}

// increment le niveau de l'upgrade par 1
void Upgrade::levelUp(){
    this->level = this->getLevel() + 1;
    this->effect();
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

