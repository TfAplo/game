#ifndef HUD_H
#define HUD_H

#include "Player.h"
#include "xpbar.h"
#include "upgrade.h"
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
    vector<QGraphicsPixmapItem*> pixItems;

public:
    HUD(Player *player,QTimer *gameTimer,QGraphicsScene *scene, QGraphicsView *view);
    void update();
    void updateTime();
    void updateItems(vector<Upgrade*> &vec);
    QString getTime();
    void hideTimer();
};

#endif // HUD_H
