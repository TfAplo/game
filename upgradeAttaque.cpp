#include "upgradeAttaque.h"

upgradeAttaque::upgradeAttaque(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,QGraphicsItem *parent)
    : Upgrade(name,description,imageIcone)
{
    this->cooldown = cooldown;
    this->animationDuration = animationDuration;
    this->imageAnimation = imageAnimation;
}


double upgradeAttaque::getCooldown() const {
    return this->cooldown;
}
double upgradeAttaque::getAnimationDuration() const {
    return this->animationDuration;
}
QString upgradeAttaque::getImageAnimation() const{
    return this->imageAnimation;
}
