#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QPoint>
#include "Player.h"
#include "hud.h"
#include "Map.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    QTimer *gameTimer;
    Player* player;
    HUD *hud;
    Map *map;

};

#endif // GAME_H
