#include "upgradeAttaque.h"

upgradeAttaque::upgradeAttaque(QString name, QString description, QString imageIcone, Player *player,double cooldown, double animationDuration, QString imageAnimation, QGraphicsItem *parent):
    Upgrade(name, description,imageIcone,player)
{
    this->cooldown = cooldown;
    this->animationDuration = animationDuration;
    this->imageAnimation = imageAnimation;
}



double upgradeAttaque::getCooldown() const{
    return this->cooldown;
}
double upgradeAttaque::getAnimationDuration() const{
    return this->animationDuration;
}
QString upgradeAttaque::getImageAnimation() const{
    return this->imageAnimation;
}

void upgradeAttaque::setActif(){
    timerCooldown = new QTimer(this);
    connect(timerCooldown, &QTimer::timeout, this, effect);
    timerCooldown->start(cooldown);
}
