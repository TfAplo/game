#include "Game.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include "Monstre.h"
#include "Vague.h"
#include <QTimer>
#include "Upgrades.h"
#include "MeleeUpgrade.h"


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
    bool side;
    player = new Player(image,position,current_hp,max_hp,speed,dmg,xp,side);

    // ajout valentin
    vector<Upgrades*> upgrades;

    QString attack_name = "THOUSAND EDGE";
    QString description = "Inflige de lourds dégâts dans la direction dans laquelle regarde votre personnage. Bien évidemment, les lames transpercent les ennemis. Cette arme légendaire est plutôt utile pour faire fondre rapidement les points de vie des boss, mais ne sera pas la plus pratique lorsque vous serez encerclé d'ennemis en fin de partie.";
    QString pathImage = ":/graphics/Tiles/tile_0104.png";
    int level = 1;
    double cooldown = 500;
    double animationDuration = 300;
    double attack_dmg = 100;
    double widthRange = 120;
    double heightRange = 100;

    MeleeUpgrade* defaultAttack = new MeleeUpgrade(attack_name,description,pathImage, level,cooldown,animationDuration, attack_dmg, widthRange, heightRange);
    MeleeUpgrade* missile = new MeleeUpgrade("missile",description,":/graphics/Tiles/tile_0120.png", level,4800,2000, 300, 300000, 300000);

    upgrades.push_back(defaultAttack);
    upgrades.push_back(missile);



    //fin ajout

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

    srand(time(0));
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

    // VALENTIN AJOUT

    // activer toutes les attaques
    for(const auto& upgrade : upgrades){
        QTimer *attackTimer = new QTimer(this);
        connect(attackTimer, &QTimer::timeout, [this, upgrade]() {
            upgrade->defaultAttack(*player,Monstre::vectMonstre);
            //afficher une image
            QGraphicsPixmapItem* attackEffect = new QGraphicsPixmapItem(QPixmap(upgrade->getPathImage()));
            attackEffect->setScale(5);
            int side = player->getSide() ? -1 : 1;
            int rota = player->getSide() ? 270 : 90;
            attackEffect->setRotation(rota);
            attackEffect->setPos(player->pos().x() + 120 * side, player->pos().y() - 16);
            scene->addItem(attackEffect);
            //supprimer l'image
            QTimer *imageRemovalTimer = new QTimer(this);
            connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect, imageRemovalTimer]() {
                scene->removeItem(attackEffect);
                delete attackEffect;
                imageRemovalTimer->deleteLater();
            });
            imageRemovalTimer->start(upgrade->getAnimationDuration());
        });
        attackTimer->start(upgrade->getCooldown());
    }
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
