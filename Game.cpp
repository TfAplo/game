#include "Game.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include <QTimer>
#include "hud.h"


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
    double xp = 50.0;
    double dmg = 10.0;
    player = new Player("image",position,current_hp,max_hp,speed,dmg,xp);

    //met le focus sur Player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    //timer du jeu
    gameTimer = new QTimer(this);

    //creation de l'HUD
    hud = new HUD(player, gameTimer,scene,this);

    //conect le timer avec les methodes des classes
    connect(gameTimer,SIGNAL(timeout()), player,SLOT(move()));
    connect(gameTimer, &QTimer::timeout, this, [this](){
        centerOn(player);
        hud->update();
    });
    gameTimer->start(20);

    show();
}
