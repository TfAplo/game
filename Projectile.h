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
    QTimer *gameTimer;
    Player *player;
    QGraphicsScene * scene;
    pair<double, double> positionM;
    pair<double, double> positionP;
    double dmg;
public:
    Projectile(Player* player,QGraphicsScene *scene,pair<double, double> positionM,QTimer *gameTimer,pair<double, double> positionP,double dmg);
signals:

public slots:
    void move();
    void destroyProjectile();
};

#endif // PROJECTILE_H
