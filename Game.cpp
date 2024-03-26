#include "Game.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include "Monstre.h"
#include "Vague.h"
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
    QString image="image";
    pair<double,double> position = make_pair(800,800);
    double current_hp = 100.0;
    double max_hp = 100.0;
    double speed = 2.5;
    double xp = 0.0;
    double dmg = 10.0;
    player = new Player(image,position,current_hp,max_hp,speed,dmg,xp);

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

    double first_circle = 200;
    double second_circle = 500;

    // on génère des coordonnées aléatoires
    pair<double,double> positionM = Game::getRandomPos(*player,first_circle,second_circle);

    Monstre *monstre =new Monstre(true,false,":/graphics/Tiles/tile_0109.png",positionM,current_hpM,max_hpM,speedM,dmgM,gameTimer,player,scene);

    pair<double,double> positionM1 = Game::getRandomPos(*player,first_circle,second_circle);

    Monstre *monstre2 =new Monstre(true,true,":/graphics/Tiles/tile_0111.png",positionM1,current_hpM,max_hpM,speedM,dmgM,gameTimer,player,scene);

    vector<Monstre*> tableauMonstres;
    tableauMonstres.push_back(monstre);
    tableauMonstres.push_back(monstre2);
    Vague *vague = new Vague(tableauMonstres,scene,gameTimer,player);


    show();
}

pair<int,int> Game::getRandomPos(Player& player, int first_circle, int second_circle){
    // random compris entre les deux rayon
    int randDist = first_circle  + rand() % (second_circle - first_circle + 1);
    double randomAngle = (rand() / (RAND_MAX / (2 * M_PI))); // Angle aléatoire
    //out << randDist <<": " <<randomAngle << Qt::endl;

    int x = player.pos().x() + randDist * cos(randomAngle);
    int y = player.pos().y() + randDist * sin(randomAngle);
    //out << x <<": " <<y << Qt::endl;
    return make_pair(x,y);
}
