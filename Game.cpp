#include "Game.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include "Monstre.h"
#include "Vague.h"
#include "Ghost.h"
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
#include <set>
#include <algorithm> // Pour std::find
#include <iostream>
using namespace std;
//fin ajout test
#include "hud.h"
//attaques
#include "Fonctions.h"
#include "upgradeAttaqueDefault.h"
#include "upgradeAttaqueShield.h"
#include "upgradePlayerSpeed.h"
#include "upgradeAttaqueSelfHeal.h"
#include "upgradeAttaqueBombes.h"
// objets
#include "bouf.h"
#include "aimant.h"


Game::Game(QWidget *parent) {
    // create the scene
    scene = new QGraphicsScene();

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map = new Map(scene);

    //creation du player
    pair<double,double> position = make_pair(1200,1200);
    double current_hp = 100.0;
    double max_hp = 100.0;
    double speed = 2.5;
    double xp = 50.0;
    double dmg = 10.0;
    double limiteXP = 100.0;
    QString qs(":/graphics/Tiles/tile_0084.png");
    player = new Player(qs,position,current_hp,max_hp,speed,dmg,xp, limiteXP);

    //met le focus sur Player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    //ajout

    connect(player, &Player::signalToGame, this, &Game::handleSignalFromPlayer);

    //fin ajout

    //timer du jeu
    gameTimer = new QTimer(this);

    //creation de l'HUD
    hud = new HUD(player, gameTimer,scene,this);

    //conect le timer avec les methodes des classes
    connect(gameTimer,SIGNAL(timeout()), player,SLOT(move()));
    connect(gameTimer, &QTimer::timeout, this, [this](){
        centerOn(player);
        //ajout
        player->recupXP();
        player->setFocus();

        //fin ajout
        hud->update();
        map->chunkUpdate(QPoint(static_cast<int>(player->pos().x()), static_cast<int>(player->pos().y())));
    });
    gameTimer->start(20);




    vector<string> tableauMonstre;
    tableauMonstre.push_back("ghost");
    tableauMonstre.push_back("sorcier");
    tableauMonstre.push_back("cyclope");
    Vague *vague = new Vague(tableauMonstre,scene,gameTimer,player);


    // AJOUT ATTAQUES
    upgradeAttaqueDefault* defaultAttaque = new upgradeAttaqueDefault(player);
    upgradeAttaqueShield* shield = new upgradeAttaqueShield(player);
    upgradePlayerSpeed* boots = new upgradePlayerSpeed(player);
    upgradeAttaqueSelfHeal* seringue = new upgradeAttaqueSelfHeal(player);
    upgradeAttaqueBombes* bombes = new upgradeAttaqueBombes(player);



    // All
    vecUpgrades.push_back(defaultAttaque);
    vecUpgrades.push_back(shield);
    vecUpgrades.push_back(boots);
    vecUpgrades.push_back(seringue);
    vecUpgrades.push_back(bombes);


    //current
    vecUpJoueur.push_back(defaultAttaque);
    vecUpJoueur.push_back(bombes);




    // non
    vecUpPasJoueur.push_back(shield);
    vecUpPasJoueur.push_back(boots);
    vecUpPasJoueur.push_back(seringue);


    //nouvel objet
    //bombe* objBombe = new bombe(scene,player);
    //objects.push_back(objBombe);

    Fonctions fonctions;
    addRandomObject(player,scene);

    QTimer* verifyCollisionObjet = new QTimer(this);
    connect(verifyCollisionObjet, &QTimer::timeout, this,[this,&fonctions](){
        // verifier si le player entre en collision avec des objets sur la map
        for(const auto& obj : objects){
            if(fonctions.isCollide(player->pos(),obj->pos())){
                obj->catchObject();
                //supprimer de la scene et du vecteur
                scene->removeItem(obj);
                //delete obj;
            }
        }
    });
    verifyCollisionObjet->start(200);



    // FIN AJOUT

    show();
}


void Game::addRandomObject(Player* player, QGraphicsScene* scene){

    int rdm = getRandomDelay(1,2);
    pair<int, int> posMeat = getRandomPos(*player,500,1000);
    QPointF pos(posMeat.first,posMeat.second);

    if(rdm == 1){
        aimant* aim = new aimant(scene,player,pos);
        objects.push_back(aim);
    } else if(rdm == 2){
        bouf* meat = new bouf(scene,player,pos);
        objects.push_back(meat);
    }


    int minDelay = 2000;
    int maxDelay = 6000;
    cout << "Speed : " <<player->getSpeed() << endl;
    int randomDelay = getRandomDelay(minDelay, maxDelay);

    QTimer::singleShot(randomDelay, [this,player, scene]() {
        addRandomObject(player, scene);
    });
}
int Game::getRandomDelay(int minDelay, int maxDelay){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minDelay, maxDelay);
    return distribution(gen);
}

pair<int,int> Game::getRandomPos(Player& player, int first_circle, int second_circle){
    // random compris entre les deux rayon
    int randDist = first_circle  + rand() % (second_circle - first_circle + 1);
    double randomAngle = (rand() / (RAND_MAX / (2 * M_PI))); // Angle aléatoire
    //cout << randDist <<": " <<randomAngle << Qt::endl;

    int x = player.pos().x() + randDist * cos(randomAngle);
    int y = player.pos().y() + randDist * sin(randomAngle);
    //cout << x <<": " <<y << Qt::endl;
    return make_pair(x,y);
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

    //definit quel objet sera dans le shop (1 nouveau et 2 du perso OU 2 nouveaux et 1 du perso)
    random_device rd;
    mt19937 gen(rd());
    int nbObjetNouveau;
    int nbObjetPasNouveau;
    if (vecUpJoueur.size() == 1) {
        nbObjetNouveau = 2;
        nbObjetPasNouveau = 1;
    } else if (vecUpPasJoueur.size() > 1) {
        uniform_int_distribution<> dis(1, 2);
        nbObjetNouveau = dis(gen);
        nbObjetPasNouveau = 3 - nbObjetNouveau;
    } else if (vecUpPasJoueur.size() == 1){
        nbObjetNouveau = 1;
        nbObjetPasNouveau = 2;
    } else {
        nbObjetNouveau = 0;
        nbObjetPasNouveau = 3;
    }

    vector<Upgrade*> vecUpgradeChoix(3);
    vector<bool> estNouveau(3);
    set<int> indicesChoisis;
    cout << nbObjetNouveau << endl;
    cout << nbObjetPasNouveau << endl;
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
        estNouveau[i] = false;
    }
    indicesChoisis.clear();
    for (int i=nbObjetPasNouveau; i<3; i++) {
        uniform_int_distribution<> dis(0, vecUpPasJoueur.size()-1);
        int indice;
        do {
            indice = dis(gen);
        } while (indicesChoisis.count(indice) > 0); // Vérifier si l'indice est déjà choisi
        vecUpgradeChoix[i] = vecUpPasJoueur[indice];
        indicesChoisis.insert(indice); // Ajouter l'indice choisi à l'ensemble
        estNouveau[i] = true;
    }


    //afficher 3 rectangles avec 3 choix
    QPointF topLeft = mapToScene(0, 0);
    QPointF topRight = mapToScene(viewport()->width(), viewport()->height());
    int largeur = topRight.x() - topLeft.x();
    int hauteur = topRight.y() - topLeft.y();
    ChoixNiveauUp *choix1 = new ChoixNiveauUp(vecUpgradeChoix[0], estNouveau[0], topLeft.x()+largeur/10, topLeft.y()+hauteur/10, (largeur/10)*2, (hauteur/10)*8, scene, this, gameTimer);
    ChoixNiveauUp *choix2 = new ChoixNiveauUp(vecUpgradeChoix[1], estNouveau[1], topLeft.x()+(largeur/10)*4, topLeft.y()+hauteur/10, (largeur/10)*2, (hauteur/10)*8, scene, this, gameTimer);
    ChoixNiveauUp *choix3 = new ChoixNiveauUp(vecUpgradeChoix[2], estNouveau[2], topLeft.x()+(largeur/10)*7, topLeft.y()+hauteur/10, (largeur/10)*2, (hauteur/10)*8, scene, this, gameTimer);
    connect(choix1, &ChoixNiveauUp::signalFinChoix, this, &Game::handleSignalFinChoix);
    connect(choix2, &ChoixNiveauUp::signalFinChoix, this, &Game::handleSignalFinChoix);
    connect(choix3, &ChoixNiveauUp::signalFinChoix, this, &Game::handleSignalFinChoix);
}

void Game::handleSignalFromPlayer() {
    this->afficherChoix();
}

void Game::handleSignalFinChoix(Upgrade *upgrade) {
    if (std::find(vecUpJoueur.begin(), vecUpJoueur.end(), upgrade) != vecUpJoueur.end()) {
        upgrade->levelUp();

    } else {
        //mettre l'upgrade dans vecUpJoueur et le supprimer de vecUpPasJoueur
        auto it = std::find(vecUpPasJoueur.begin(), vecUpPasJoueur.end(), upgrade);
        vecUpJoueur.push_back(std::move(*it));
        upgrade->setActif();

        // Supprimer l'élément de vecUpPasJoueur
        vecUpPasJoueur.erase(it);
    }

    cout << "vecUpJoueur : ";
    for (Upgrade *upgrade : vecUpJoueur) {
        cout << upgrade->getName().toStdString() << " lvl " << upgrade->getLevel() << " - ";
    }
    cout << endl;
    cout << "vecUpPasJoueur : ";
    for (Upgrade *upgrade : vecUpPasJoueur) {
        cout << upgrade->getName().toStdString() << " lvl " << upgrade->getLevel()  << " - ";
    }
    cout << endl;
}

//fin ajout

