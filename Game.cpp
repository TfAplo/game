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
//attaques
#include "Fonctions.h"
#include "upgradeAttaqueDefault.h"
#include "upgradeAttaqueShield.h"
#include "upgradePlayerSpeed.h"
#include "upgradeAttaqueSelfHeal.h"
#include "upgradeAttaqueArc.h"
#include "upgradeAttaqueHache.h"
#include "upgradePlayerArmor.h"
#include "upgradePlayerHealth.h"
#include "upgradeAttaqueBombes.h"

// objets
#include "bouf.h"
#include "aimant.h"


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


    int minDelay = 20000;
    int maxDelay = 60000;
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

    int x = player.pos().x() + randDist * cos(randomAngle);
    int y = player.pos().y() + randDist * sin(randomAngle);
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
    inGame = false;
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
        endgame();
    });
    gameTimer->start(20);

    vector<string> tableauMonstre;
    tableauMonstre.push_back("ghost");
    tableauMonstre.push_back("sorcier");
    tableauMonstre.push_back("cyclope");
    vague = new Vague(tableauMonstre,scene,gameTimer,player);

    // AJOUT ATTAQUES
    upgradeAttaqueDefault* defaultAttaque = new upgradeAttaqueDefault(player,gameTimer);
    upgradeAttaqueShield* shield = new upgradeAttaqueShield(player,gameTimer);
    upgradePlayerSpeed* boots = new upgradePlayerSpeed(player);
    upgradeAttaqueSelfHeal* seringue = new upgradeAttaqueSelfHeal(player,gameTimer);
    upgradeAttaqueBombes* bombes = new upgradeAttaqueBombes(player,gameTimer);
    //upgradeAttaqueArc* arc = new upgradeAttaqueArc(player, gameTimer);
    upgradeAttaqueHache* hache = new upgradeAttaqueHache(player, gameTimer);
    upgradePlayerArmor* armor = new upgradePlayerArmor(player);
    upgradePlayerHealth* health = new upgradePlayerHealth(player);


    // All
    vecUpgrades.push_back(defaultAttaque);
    vecUpgrades.push_back(shield);
    vecUpgrades.push_back(boots);
    vecUpgrades.push_back(seringue);
    //vecUpgrades.push_back(arc);
    vecUpgrades.push_back(hache);
    vecUpgrades.push_back(armor);
    vecUpgrades.push_back(health);
    vecUpgrades.push_back(bombes);


    //current
    vecUpJoueur.push_back(defaultAttaque);
    //mettre a jour l'hud
    hud->updateItems(vecUpJoueur);

    // non
    vecUpPasJoueur.push_back(shield);
    vecUpPasJoueur.push_back(boots);
    vecUpPasJoueur.push_back(seringue);
    vecUpPasJoueur.push_back(bombes);
    //vecUpPasJoueur.push_back(arc);
    vecUpPasJoueur.push_back(hache);
    vecUpPasJoueur.push_back(armor);
    vecUpPasJoueur.push_back(health);

    Fonctions fonctions;
    addRandomObject(player,scene);

    QTimer* verifyCollisionObjet = new QTimer(this);
    connect(verifyCollisionObjet, &QTimer::timeout, this, [this, &fonctions]() {
        // Vecteur pour stocker les indices des objets Ã  supprimer
        QVector<int> indicesToDelete;

        // Parcourir les objets dans le vecteur
        for (int i = 0; i < objects.size(); ++i) {
            auto obj = objects[i];
            if (fonctions.isCollide(player->pos(), obj->pos())) {
                obj->catchObject();
                scene->removeItem(obj);
                indicesToDelete.append(i);
            }
        }
        for (int i = indicesToDelete.size() - 1; i >= 0; --i) {
            int index = indicesToDelete[i];
            delete objects[index];
            objects.erase(objects.begin() + index);
        }
    });
    verifyCollisionObjet->start(200);

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

void Game::wheelEvent(QWheelEvent *event)
{
    event->ignore();
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

void Game::endgame()
{
    if(player->getCurrent_hp() == 0){
        inGame=false;
        gameTimer->stop();
        player->hideXPBar();
        hud->hideTimer();
        player->setPixmap(QPixmap(":/graphics/Tiles/tile_0064.png").scaled(32, 32));
        // Créer un rectangle qui prend la plus part de l'écran au milieu
        int screenWidth = 1280;
        int screenHeight = 720;
        int rectWidth = 500;
        int rectHeight = 600;
        QPointF topLeft = mapToScene(0, 0);
        int rectX = (screenWidth - rectWidth) / 2 + topLeft.x();
        int rectY = (screenHeight - rectHeight) / 2 + topLeft.y();

        QGraphicsRectItem *fond = new QGraphicsRectItem(topLeft.x(), topLeft.y(), 1280, 720);
        fond->setBrush(QColor(0, 0, 0, 230));
        scene->addItem(fond);

        QGraphicsRectItem *rectangle = new QGraphicsRectItem(rectX, rectY, rectWidth, rectHeight);
        rectangle->setPen(QPen(Qt::white));
        scene->addItem(rectangle);

        // Créer un label "Game Over"
        gameOverLabel = new QGraphicsTextItem("Game Over");
        gameOverLabel->setDefaultTextColor(Qt::red);
        gameOverLabel->setFont(QFont("Arial", 60, QFont::Bold));
        gameOverLabel->setPos(rectX + rectWidth/2 - gameOverLabel->boundingRect().width()/2,rectY + 20);
        scene->addItem(gameOverLabel);

        // Créer un label "Time Survived: "
        gameTimeLabel = new QGraphicsTextItem("Time Survived: "+ hud->getTime());
        gameTimeLabel->setDefaultTextColor(Qt::white);
        gameTimeLabel->setFont(QFont("Arial", 20, QFont::Bold));
        gameTimeLabel->setPos(rectX + rectWidth/2 - gameTimeLabel->boundingRect().width()/2,rectY + 120);
        scene->addItem(gameTimeLabel);

        // Créer un label "Level Achieved: "
        gameTimeLabel = new QGraphicsTextItem("Level Achieved: " +QString::number(player->getNiveau()));
        gameTimeLabel->setDefaultTextColor(Qt::white);
        gameTimeLabel->setFont(QFont("Arial", 20, QFont::Bold));
        gameTimeLabel->setPos(rectX + rectWidth/2 - gameTimeLabel->boundingRect().width()/2,rectY + 180);
        scene->addItem(gameTimeLabel);

        // Créer un bouton "Back to Menu" en bas du rectangle
        buttonBackToMenu->setGeometry(rectX+rectWidth/2-buttonBackToMenu->width()/2, rectY+500, buttonBackToMenu->width(), buttonBackToMenu->height());
        buttonBackToMenu->setVisible(true);
    }
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
        //mettre a jour l'hud
        hud->updateItems(vecUpJoueur);
    }
    inGame=true;
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

