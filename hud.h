#ifndef HUD_H
#define HUD_H

#include "Player.h"
#include "xpbar.h"
#include <QTimer>
#include <QTime>

class HUD
{
private:
    Player *player;
    QTimer *gameTimer;
    XPBar *xpBar;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsTextItem *labelTimer;
    QTime startTime;

public:
    HUD(Player *player,QTimer *gameTimer,QGraphicsScene *scene, QGraphicsView *view);
    void update();
    void updateTime();
};

#endif // HUD_H
