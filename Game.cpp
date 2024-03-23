#include "Game.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include "Monstre.h"
#include <QTimer>


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
    player = new Player("image",position,current_hp,max_hp,speed,dmg,xp);

    //met le focus sur Player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    //timer du jeu
    gameTimer = new QTimer(this);
    //conect le timer avec les methodes des classes
    connect(gameTimer,SIGNAL(timeout()), player,SLOT(move()));
    connect(gameTimer, &QTimer::timeout, this, [this](){
        centerOn(player);
    });
    gameTimer->start(20);

    double current_hpM = 100.0;
    double max_hpM = 100.0;
    double speedM = 1.;
    double dmgM = 10.0;

    int rand_min = 0;
    int rand_max = 1600;

    // on génère des coordonnées aléatoires
    int coord1 = arc4random_uniform(rand_max - rand_min + 1) + rand_min;
    int coord2 = arc4random_uniform(rand_max - rand_min + 1) + rand_min;
    pair<double,double> positionM = make_pair(coord1,coord2);

    Monstre *monstre =new Monstre("image",positionM,current_hpM,max_hpM,speedM,dmgM,player,scene);
    scene->addItem(monstre);

    show();
}
