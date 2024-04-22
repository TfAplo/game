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
#include <ctime>
using namespace std;
//fin ajout test
#include "hud.h"
//attaques
#include "upgradeAttaqueMelee.h"
#include "upgradeAttaqueShield.h"
#include "upgradePlayer.h"
#include "upgradeSpeed.h"
#include "upgradeHealth.h"
#include "upgradeAttaqueArc.h"
#include "upgradeAttaqueHache.h"
#include "upgradePlayerCoeur.h"
#include "Meat.h"


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
    srand(time(0));

    //ajout
    /*
    connect(player, &Player::signalToGame, this, &Game::handleSignalFromPlayer);

    vector<pair<string, string>> vecUpgradeNoms = {
        {"Arme", "Epee"},
        {"Arme", "Hache"},
        {"Arme", "Sceptre"},
        {"Gadget", "Chaussures"},
        {"Gadget", "Ailes"},
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
*/

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

    QString attack_name = "THOUSAND EDGE";
    QString description = "Inflige de lourds dégâts dans la direction dans laquelle regarde votre personnage. Bien évidemment, les lames transpercent les ennemis. Cette arme légendaire est plutôt utile pour faire fondre rapidement les points de vie des boss, mais ne sera pas la plus pratique lorsque vous serez encerclé d'ennemis en fin de partie.";
    QString pathImage = ":/graphics/Tiles/tile_0104.png";
    double cooldown = 500;
    double animationDuration = 300;
    double widthRange = 120;
    double heightRange = 50;

    upgradeAttaqueMelee* defaultAttack = new upgradeAttaqueMelee(attack_name,description,pathImage,pathImage,cooldown,animationDuration, widthRange, heightRange);
    upgradeAttaqueShield* shield = new upgradeAttaqueShield("SHIELD","inflige des degats aux ennemis trop proche",":/graphics/Tiles/tile_0061.png",":/graphics/Tiles/tile_0061.png",400,0,100,50);
    upgradeSpeed* SuperBoots = new upgradeSpeed("Super Boots","Augmente la vitesse de 10%",":/graphics/Tiles/tile_0020.png",10);
    upgradeHealth* PotionHealth = new upgradeHealth("Potion de Vie ","Provoque un effet de regeneration",":/graphics/Tiles/tile_0030.png",10);
    upgradeAttaqueArc* arc = new upgradeAttaqueArc("Arc","Inflige des degats important à longue distance",":/graphics/UpgradeImages/Arc.png",":/graphics/UpgradeImages/Arc.png",0,0,120,50);
    upgradeAttaqueHache* hache = new upgradeAttaqueHache("Hache","Inflige de lourdes attaques des deux cotes du personnage",":/graphics/UpgradeImages/Hache.png",":/graphics/UpgradeImages/Hache.png",1500,350,80,85);
    upgradePlayerCoeur* coeur = new upgradePlayerCoeur("Coeur supplementaire","Augmente les pv max de 15%",":/graphics/UpgradeImages/coeur.png",15);

    // toutes les upgrades disponibles
    vector<Upgrade*> upgrades;
    upgrades.push_back(defaultAttack);
    upgrades.push_back(shield);
    upgrades.push_back(SuperBoots);
    upgrades.push_back(PotionHealth);
    upgrades.push_back(hache);
    upgrades.push_back(coeur);

    // toutes les upgrades indisponible pour le moment
    vector<Upgrade*> non_upgrades;
    non_upgrades.push_back(shield);
    non_upgrades.push_back(SuperBoots);
    non_upgrades.push_back(arc);
    non_upgrades.push_back(hache);
    non_upgrades.push_back(coeur);

    //upgrades d'attaques appliqué dans la partie
    vector<Upgrade*> current_upgrades;
    //current_upgrades.push_back(defaultAttack);
    current_upgrades.push_back(PotionHealth);

    // activer toutes les attaques
    for(const auto& upgrade : current_upgrades){
        cout << upgrade->getName().toStdString() << endl;
        // test si l'upgrade est une instance de upgradeAttaque
        if(upgradeAttaque* attackUpgrade = dynamic_cast<upgradeAttaque*>(upgrade)){
            QTimer *attackTimer = new QTimer(this);
            connect(attackTimer, &QTimer::timeout, [this, attackUpgrade]() {
                attackUpgrade->defaultAttack(*player,Monstre::vectMonstre);
                attackUpgrade->affichage(*player,*attackUpgrade,*scene);
            });
            attackTimer->start(attackUpgrade->getCooldown());
        }
        else {
            // objet à utiliser une seule fois
            if(upgradePlayer* upgrade_Player = dynamic_cast<upgradePlayer*>(upgrade)){
                if(upgrade_Player->getIsUsed() == false){
                    upgrade_Player->defaultAttack(*player);
                    upgrade_Player->setIsUsed(true);
                }
            }
        }
    }

    // ajouter des objets au sol temps aleatoire entre 20s et 60s
    addRandomObject(player,scene);

    QTimer *objectTimer = new QTimer(this);
    connect(objectTimer, &QTimer::timeout, [this]() {
        auto it = objects.begin();
        while (it != objects.end()) {
            auto object = *it;

            if (object) {
                // Vérifiez les conditions de collision
                if (object->getPosition().first >= player->pos().x() && object->getPosition().first <= player->pos().x() + 32 ||
                    object->getPosition().first <= player->pos().x() && object->getPosition().first > player->pos().x() + 32) {
                    if (object->getPosition().second <= player->pos().y() + (32 / 2) && object->getPosition().second >= player->pos().y() - (32 / 2)) {
                        object->catchObject(*player);
                        // Supprimez l'objet de la scène et du vector
                        scene->removeItem(object);
                        delete object;
                        it = objects.erase(it); // Effacez l'élément du vector
                        continue; // Passez à l'élément suivant
                    }
                }
            }

            ++it;
        }
    });
    objectTimer->start(100);

    // FIN AJOUT

    show();
}


void Game::addRandomObject(Player* player, QGraphicsScene* scene){
    pair<int,int> pos = getRandomPos(*player, 500, 1500);
    cout << pos.first <<": " << pos.second << endl;
    Meat* meat = new Meat(":/graphics/Tiles/tile_0101.png", pos);
    QGraphicsPixmapItem* itemMeat = new QGraphicsPixmapItem(QPixmap(meat->getImage()));
    itemMeat->setScale(4);
    itemMeat->setPos(pos.first, pos.second);
    scene->addItem(itemMeat);
    objects.push_back(meat);

    int minDelay = 20000;
    int maxDelay = 60000;
    int randomDelay = getRandomDelay(minDelay, maxDelay);

    cout << "spawn" << endl;

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
    if (vecUpPasJoueur.size() > 1) {
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

        // Supprimer l'élément de vecUpPasJoueur
        vecUpPasJoueur.erase(it);
    }

    cout << "vecUpJoueur : ";
    for (Upgrade *upgrade : vecUpJoueur) {
        cout << upgrade->getName().toStdString() << "lvl " << upgrade->getLevel() << " - ";
    }
    cout << endl;
    cout << "vecUpPasJoueur : ";
    for (Upgrade *upgrade : vecUpPasJoueur) {
        cout << upgrade->getName().toStdString() << "lvl " << upgrade->getLevel()  << " - ";
    }
    cout << endl;
}

//fin ajout

