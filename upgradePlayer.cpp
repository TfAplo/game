#include "upgradePlayer.h"

upgradePlayer::upgradePlayer(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent)
    : Upgrade(name,description,imageIcone,parent){
    this->boostValue = boostValue;
    this->isUsed = false;
}


int upgradePlayer::getBoostValue() const{
    return this->boostValue;
}
void upgradePlayer::setBoostValue(int v){
    this->boostValue = v;
}

bool upgradePlayer::getIsUsed() const{
    return this->isUsed;
}

void upgradePlayer::setIsUsed(bool b){
    this->isUsed = b;
}

//void upgradePlayer::defaultAttack(){}
