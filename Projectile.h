#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include <QTimer>
#include <QGraphicsObject>
#include "Player.h"


class Projectile:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QTimer *moveTimer;
    Player *player;
    QGraphicsScene * scene;
    pair<double, double> positionM;
public:
    Projectile(Player *player,QGraphicsScene * scene,pair<double, double> positionM);
signals:

public slots:
    void move();
};

#endif // PROJECTILE_H
