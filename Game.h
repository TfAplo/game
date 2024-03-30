#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"
#include "upgrade.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);

    QGraphicsScene * scene;
    QTimer *gameTimer;
    Player* player;

    //ajout
    int nbObjetPossible;
    map<string, string> mapUpgradeNoms;
    vector<Upgrade*> vecUpgrades; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu
    vector<Upgrade*> vecUpJoueur; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu
    vector<Upgrade*> vecUpPasJoueur; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu

    static double calculDistance(pair<double, double>, pair<double, double>);
    void afficherChoix();

public slots:
    void handleSignalFromPlayer();
    void handleSignalFinChoix();
// fin ajout
};

#endif // GAME_H
