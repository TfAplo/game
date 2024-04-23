#include "Game.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include "Vague.h"
#include <QTimer>
#include <cmath>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include "ChoixNiveauUp.h"
#include "upgrade.h"
#include <random> // pour std::random_device et std::mt19937
#include <set>
#include <algorithm> // Pour std::find
using namespace std;
#include "hud.h"
#include <QApplication>
#include "Wizard.h"
#include "Tank.h"
#include "Runner.h"


Game::Game(QWidget *parent) {
    //créer la scene de menu
    menu = new Menu();
    connect(menu, &Menu::onPlaySignal, this, &Game::handleSignalPlay);
    connect(menu, &Menu::onExitSignal, this, &Game::handleSignalExit);
    //masque les barres de défilement
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1280,720);
    setScene(menu);

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

void Game::makeNewGame(QString choixPerso)
{
    inGame = true;
    // creer une scene
    scene = new QGraphicsScene();

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);

    //creation du menu de pause
    buildPauseMenu();

    map = new Map(scene);

    if (choixPerso == "Wizard") {
        player = new Wizard();
    } else if (choixPerso == "Tank") {
        player = new Tank();
    } else if (choixPerso == "Runner") {
        player = new Runner();
    }

    //met le focus sur Player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

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

    //timer du jeu
    gameTimer = new QTimer(this);

    //creation de l'HUD
    hud = new HUD(player, gameTimer,scene,this);

    //conect le timer avec les methodes des classes
    connect(gameTimer,SIGNAL(timeout()), player,SLOT(move()));
    connect(gameTimer, &QTimer::timeout, this, [this](){
        centerOn(player);
        player->recupXP();
        player->setFocus();
        hud->update();
        map->chunkUpdate(QPoint(static_cast<int>(player->pos().x()), static_cast<int>(player->pos().y())));
    });
    gameTimer->start(20);

    vector<string> tableauMonstre;
    tableauMonstre.push_back("ghost");
    tableauMonstre.push_back("sorcier");
    tableauMonstre.push_back("cyclope");
    vague = new Vague(tableauMonstre,scene,gameTimer,player);

    show();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
    if (event->key() == Qt::Key_Escape){
        if (inGame){
            if (pauseMenuOut){
                handleResumeClicked();
            }
            else{
                //mettre le jeu en pause et afficher le menu
                pauseMenuOut = true;
                this->gameTimer->stop();
                buttonResume->setVisible(true);
                QPointF topLeft = mapToScene(0, 0);
                buttonResume->setGeometry(448 + topLeft.x(),232+topLeft.y(),buttonResume->width(),buttonResume->height());
                buttonBackToMenu->setVisible(true);
                buttonBackToMenu->setGeometry( 448+ topLeft.x(),324+topLeft.y(),buttonBackToMenu->width(),buttonBackToMenu->height());
                buttonExit->setVisible(true);
                buttonExit->setGeometry(448 + topLeft.x(), 416+topLeft.y(),buttonExit->width(),buttonExit->height());

            }
        }
    }
}

void Game::buildPauseMenu()
{
    //buttonExit est deja utilisé dans une autre scene:
    QPushButton *oldResumeButton = menu->getButtonResume();
    QPushButton *oldBackToMenuButton = menu->getButtonBackToMenu();
    QPushButton *oldExitButton = menu->getButtonExit();

    buttonExit = new QPushButton(oldExitButton->text());
    buttonExit->setGeometry(oldExitButton->geometry());
    buttonExit->setStyleSheet(oldExitButton->styleSheet());

    buttonBackToMenu = new QPushButton(oldBackToMenuButton->text());
    buttonBackToMenu->setGeometry(oldBackToMenuButton->geometry());
    buttonBackToMenu->setStyleSheet(oldBackToMenuButton->styleSheet());

    buttonResume = new QPushButton(oldResumeButton->text());
    buttonResume->setGeometry(oldResumeButton->geometry());
    buttonResume->setStyleSheet(oldResumeButton->styleSheet());

    buttonResume->setVisible(false);
    buttonBackToMenu->setVisible(false);
    buttonExit->setVisible(false);

    connect(buttonResume,&QPushButton::clicked,this,&Game::handleResumeClicked);
    connect(buttonBackToMenu,&QPushButton::clicked,this,&Game::handleBackToMenuClicked);
    connect(buttonExit,&QPushButton::clicked,this,&Game::handleExitClicked);

    // Ajouter les boutons à la scène
    QGraphicsProxyWidget *resumeProxy = scene->addWidget(buttonResume);
    QGraphicsProxyWidget *backToMenuProxy = scene->addWidget(buttonBackToMenu);
    QGraphicsProxyWidget *exitProxy = scene->addWidget(buttonExit);
    proxis.push_back(resumeProxy);
    proxis.push_back(backToMenuProxy);
    proxis.push_back(exitProxy);

    // Définir une valeur Z élevée pour les proxies des boutons
    resumeProxy->setZValue(10);
    backToMenuProxy->setZValue(10);
    exitProxy->setZValue(10);

}

void Game::handleSignalFromPlayer() {
    this->afficherChoix();
}

void Game::handleSignalFinChoix(Upgrade *upgrade) {
    if (std::find(vecUpJoueur.begin(), vecUpJoueur.end(), upgrade) != vecUpJoueur.end()) {
        upgrade->incrementerNiveau();
    } else {
        //mettre l'upgrade dans vecUpJoueur et le supprimer de vecUpPasJoueur
        auto it = std::find(vecUpPasJoueur.begin(), vecUpPasJoueur.end(), upgrade);
        vecUpJoueur.push_back(std::move(*it));

        // Supprimer l'élément de vecUpPasJoueur
        vecUpPasJoueur.erase(it);
    }

    cout << "vecUpJoueur : ";
    for (Upgrade *upgrade : vecUpJoueur) {
        cout << upgrade->getNom() << "lvl " << upgrade->getNiveau() << " - ";
    }
    cout << endl;
    cout << "vecUpPasJoueur : ";
    for (Upgrade *upgrade : vecUpPasJoueur) {
        cout << upgrade->getNom() << "lvl " << upgrade->getNiveau()  << " - ";
    }
    cout << endl;
}

void Game::handleSignalPlay(QString name)
{
    makeNewGame(name);
}

void Game::handleSignalExit()
{
    QApplication::instance()->quit();
}

void Game::handleResumeClicked()
{
    //enlever le menu de pause et reprendre partie
    buttonResume->setVisible(false);
    buttonBackToMenu->setVisible(false);
    buttonExit->setVisible(false);

    pauseMenuOut = false;
    this->gameTimer->start(20);
}

void Game::handleBackToMenuClicked()
{
    inGame = false;
    pauseMenuOut = false;
    delete vague;
    for(Monstre* monstre: Monstre::vectMonstre){
        delete monstre;
    }
    Monstre::vectMonstre.clear();
    for(OrbeXP* orbe: OrbeXP::vecOrbeXP){
        delete orbe;
    }
    OrbeXP::vecOrbeXP.clear();
    for (const auto& proxi: proxis){
        scene->removeItem(proxi);
    }
    proxis.clear();
    delete map;
    delete player;
    delete gameTimer;
    delete buttonBackToMenu;
    delete buttonResume;
    delete buttonExit;
    vecUpJoueur.clear();
    vecUpPasJoueur.clear();
    vecUpgrades.clear();

    setScene(menu);
}

void Game::handleExitClicked()
{
    QApplication::instance()->quit();
}

