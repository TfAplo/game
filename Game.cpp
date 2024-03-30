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
#include "ChoixNiveauUp.h"
#include "upgrade.h"
#include <random> // pour std::random_device et std::mt19937
#include <map>
#include <set>
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
    for (int i=0; i<40; i++) {
        OrbeXP* orbe = new OrbeXP("Orbe", make_pair(40*i, 40*i), 30);
    }
    connect(player, &Player::signalToGame, this, &Game::handleSignalFromPlayer);

    vector<pair<string, string>> vecUpgradeNoms = {
        {"Arme", "Epee"},
        {"Arme", "Fouet"},
        {"Arme", "Shuriken"},
        {"Gadget", "Chaussure"},
        {"Gadget", "Aile"},
        {"Gadget", "Armure"}
    };
    vecUpgrades = Upgrade::initUpgrade(vecUpgradeNoms);
    bool arme = false, gadget = false;
    for (Upgrade* upgrade : vecUpgrades) {
        if (upgrade->estArme()) {
            if (!arme) {
                arme = true;
                vecUpJoueur.push_back(upgrade);
            } else {
                vecUpPasJoueur.push_back(upgrade);
            }
        } else if (upgrade->estGadget()) {
            if (!gadget) {
                gadget = true;
                vecUpJoueur.push_back(upgrade);
            } else {
                vecUpPasJoueur.push_back(upgrade);
            }
        }
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

    show();
}


// ajout
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

    //definit quel objet sera dans le shop (1 ou 2 du perso et 2 ou 1 nouveau)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 2);
    int nbObjetNouveau = dis(gen);
    int nbObjetPasNouveau = 3 - nbObjetNouveau;

    vector<Upgrade*> vecUpgradeChoix(3);
    set<int> indicesChoisis;
    for (int i=0; i<nbObjetPasNouveau; i++) { //i<nbObjetPasNouveau
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, vecUpJoueur.size()-1);
        int indice;
        do {
            indice = dis(gen);
        } while (indicesChoisis.count(indice) > 0); // Vérifier si l'indice est déjà choisi
        vecUpgradeChoix[i] = vecUpJoueur[indice];
        indicesChoisis.insert(indice); // Ajouter l'indice choisi à l'ensemble
    }

    for (int i=nbObjetPasNouveau; i<3; i++) {
        uniform_int_distribution<> dis(0, vecUpPasJoueur.size()-1);
        int indice;
        do {
            indice = dis(gen);
        } while (indicesChoisis.count(indice) > 0); // Vérifier si l'indice est déjà choisi
        vecUpgradeChoix[i] = vecUpPasJoueur[indice];
        indicesChoisis.insert(indice); // Ajouter l'indice choisi à l'ensemble
    }

    //afficher 3 rectangles avec 3 choix
    QPointF topLeft = mapToScene(0, 0);
    QPointF topRight = mapToScene(viewport()->width(), viewport()->height());
    int largeur = topRight.x() - topLeft.x();
    int hauteur = topRight.y() - topLeft.y();
    ChoixNiveauUp *choix1 = new ChoixNiveauUp(vecUpgradeChoix[0], topLeft.x()+largeur/10, topLeft.y()+hauteur/10, (largeur/10)*2, (hauteur/10)*8, scene, this, gameTimer);
    ChoixNiveauUp *choix2 = new ChoixNiveauUp(vecUpgradeChoix[1], topLeft.x()+(largeur/10)*4, topLeft.y()+hauteur/10, (largeur/10)*2, (hauteur/10)*8, scene, this, gameTimer);
    ChoixNiveauUp *choix3 = new ChoixNiveauUp(vecUpgradeChoix[2], topLeft.x()+(largeur/10)*7, topLeft.y()+hauteur/10, (largeur/10)*2, (hauteur/10)*8, scene, this, gameTimer);
    connect(choix1, &ChoixNiveauUp::signalFinChoix, this, &Game::handleSignalFinChoix);
    connect(choix2, &ChoixNiveauUp::signalFinChoix, this, &Game::handleSignalFinChoix);
    connect(choix3, &ChoixNiveauUp::signalFinChoix, this, &Game::handleSignalFinChoix);
    //signal pb pas recu
    //pas 2 fois le meme objet (FINI)
}

void Game::handleSignalFromPlayer() {
    this->afficherChoix();
}

void Game::handleSignalFinChoix() {
    cout << "valentinnn" << endl;
}

//fin ajout
