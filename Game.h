#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    static pair<int,int> getRandomPos(Player& player, int first_circle, int second_circle);

    QGraphicsScene * scene;
    QTimer *gameTimer;
    Player* player;

};

#endif // GAME_H
