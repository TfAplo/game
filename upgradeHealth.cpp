#include "upgradeHealth.h"
#include <QTimer>

using namespace std;

upgradeHealth::upgradeHealth(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent)
    : upgradePlayer(name,description,imageIcone,boostValue,parent){}

void upgradeHealth::regenerationPV(Player& player){
    player.setCurrentHp(player.getCurrent_hp() + player.getMaxHp() * this->getLevel() * this->getBoostValue() * 0.1);
}

void upgradeHealth::defaultAttack(Player& player){
    QTimer *regenerationTimer = new QTimer(this);
    connect(regenerationTimer, &QTimer::timeout, this, &upgradeHealth::regenerationPV);


    double pourcentage = static_cast<double>(this->getLevel() * this->getBoostValue()) / 100.0;
    double toAdd = pourcentage * player.getMaxHp();
    player.setMaxHp(player.getMaxHp() + toAdd);
}
/*
QTimer *imageRemovalTimer = new QTimer(this);
connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect, imageRemovalTimer, &scene]() {
    scene.removeItem(attackEffect);
    delete attackEffect;
    imageRemovalTimer->deleteLater();
});*/
