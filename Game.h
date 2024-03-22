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

    QGraphicsScene * scene;
    QTimer *gameTimer;
    Player* player;

    //ajout
    void stopTimer(); // ici stop le timer (donc affichage, mouvement et attaque des ennemis et du player
    void gererClicChoix(); // ici appeler methode de valentin
    static double calculDistance(pair<double, double>, pair<double, double>);
    void afficherChoix();
    // fin ajout
};

#endif // GAME_H
