#include "upgradePlayer.h"

upgradePlayer::upgradePlayer(QString name, QString description, QString imageIcone, Player *player,int valueBoost,QGraphicsItem *parent):
    Upgrade(name, description,imageIcone,player)
{
    this->valueBoost = valueBoost;
}


void upgradePlayer::setValueBoost(int b){
    this->valueBoost = b;
}
int upgradePlayer::getValueBoost() const{
    return this->valueBoost;
}


void upgradePlayer::setActif(){
    QTimer::singleShot(0, this, &upgradePlayer::effect);
}
