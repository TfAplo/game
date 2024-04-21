#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QPoint>
#include "Player.h"
#include "upgrade.h"
#include "hud.h"
#include "Map.h"
#include <map>
#include "ObjectOnFloor.h"

class Game: public QGraphicsView{

private:
    vector<ObjectOnFloor*> objects;
public:
    Game(QWidget * parent=0);
    static pair<int,int> getRandomPos(Player& player, int first_circle, int second_circle);

    QGraphicsScene * scene;
    QTimer *gameTimer;
    Player* player;
    HUD *hud;
    Map *map;

    //ajout
    int nbObjetPossible;
    std::map<string, string> mapUpgradeNoms;
    vector<Upgrade*> vecUpgrades; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu
    vector<Upgrade*> vecUpJoueur; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu
    vector<Upgrade*> vecUpPasJoueur; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu

    static double calculDistance(pair<double, double>, pair<double, double>);
    void afficherChoix();
    // AJOUT VALENTIN
    void addRandomObject(Player* player, QGraphicsScene* scene);
    int getRandomDelay(int minDelay, int maxDelay);

public slots:
    void handleSignalFromPlayer();
    void handleSignalFinChoix(Upgrade *upgrade);
// fin ajout
};

#endif // GAME_H
