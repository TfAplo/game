#ifndef UPGRADEATTAQUE_H
#define UPGRADEATTAQUE_H

#include "upgrade.h"
#include <QTimer>

class upgradeAttaque : public Upgrade
{
protected:
    int elapsed;
private:
    double cooldown; // duree de rechargement de l'attaque
    double animationDuration; //duree animation
    QString imageAnimation; // image utiliser pour l'animation
    QTimer* timerCooldown;

public:
    upgradeAttaque(QString name, QString description,QString imageIcone, Player* player,double cooldown, double animationDuration, QString imageAnimation,QTimer* gameTimer,QGraphicsItem *parent = 0);

    virtual void effect() = 0;
    virtual void setActif();

    void timer();

    double getCooldown() const;
    double getAnimationDuration() const;
    QString getImageAnimation() const;

};

#endif // UPGRADEATTAQUE_H
