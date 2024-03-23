#ifndef HUD_H
#define HUD_H

#include "Player.h"
#include "xpbar.h"
#include <QTimer>

class HUD
{
private:
    Player *player;
    QTimer *gameTimer;
    XPBar *xpBar;
    QGraphicsScene *scene;
    QGraphicsView *view;

public:
    HUD(Player *player,QTimer *gameTimer,QGraphicsScene *scene, QGraphicsView *view);
    void update();
};

#endif // HUD_H
