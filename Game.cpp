#include "Game.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include <QTimer>
#include <cmath>

//ajout test
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include "OrbeXP.h"
using namespace std;
//fin ajout test


Game::Game(QWidget *parent) {
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1600,1600);

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Map map(QString(":/Niveau2.csv"));
    map.afficher(scene);

    //creation du player
    pair<double,double> position = make_pair(800,800);
    double current_hp = 100.0;
    double max_hp = 100.0;
    double speed = 2.5;
    double xp = 0.0;
    double dmg = 10.0;
    double limiteXP = 100.0;
    player = new Player("image",position,current_hp,max_hp,speed,dmg,xp, limiteXP);

    //met le focus sur Player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    //ajout
    for (int i=0; i<10; i++) {
        OrbeXP* orbe = new OrbeXP("Orbe", make_pair(40*i, 40*i), 30);
    }
    //fin ajout

    //timer du jeu
    gameTimer = new QTimer(this);
    //conect le timer avec les methodes des classes
    connect(gameTimer,SIGNAL(timeout()), player,SLOT(move()));
    connect(gameTimer, &QTimer::timeout, this, [this](){
        centerOn(player);
        //ajout
        player->recupXP();
        player->setFocus();
        //fin ajout
    });
    gameTimer->start(20);

    afficherChoix();

    show();
}


// ajout
void Game::stopTimer() {

}

void Game::gererClicChoix() {

}

double Game::calculDistance(pair<double, double> point1, pair<double, double> point2) {
    double x1 = point1.first;
    double y1 = point1.second;
    double x2 = point2.first;
    double y2 = point2.second;

    double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    return distance;
}

void Game::afficherChoix() {
    // stop la partie
    gameTimer->stop();

    //afficher 3 rectangles avec 3 choix
    QGraphicsRectItem *rectItem = new QGraphicsRectItem(0, 0, 200, 200);
    rectItem->setPos(50, 50);

    scene->addItem(rectItem);
    //choix 1 : Epee lvl2
    //choix 1 : Shuriken lvl1
    //choix 3 : Chaussure lvl1
    //si clique ou bouton entrée sur choix 1 : appeler upgrade(epee)
    //si clique ou bouton entrée sur choix 2 : appeler creerObjet(shuriken)
    //si clique ou bouton entrée sur choix 3 : appeler creerObjet(Chaussure)

    // relance la partie
    gameTimer->start();
}

//fin ajout
