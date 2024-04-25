#include "upgradeAttaque.h"
#include <iostream>
using namespace std;

upgradeAttaque::upgradeAttaque(QString name, QString description, QString imageIcone, Player *player,double cooldown, double animationDuration, QString imageAnimation, QTimer* gameTimer,QGraphicsItem *parent):
    Upgrade(name, description,imageIcone,player)
{
    this->cooldown = cooldown;
    this->animationDuration = animationDuration;
    this->imageAnimation = imageAnimation;
    this->timerCooldown = gameTimer;
    this->elapsed = 0;
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
    connect(timerCooldown, &QTimer::timeout, this, &upgradeAttaque::timer);
}

void upgradeAttaque::timer(){
    if(elapsed * 20 == cooldown){
        this->effect();
        this->elapsed = 0;
    }
    this->elapsed += 1;
}
