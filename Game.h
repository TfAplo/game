#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QPoint>
#include "Player.h"
#include "upgrade.h"
#include "hud.h"
#include "Map.h"
#include <map>
#include <QPushButton>
#include "Menu.h"
#include <QGraphicsProxyWidget>
#include "Vague.h"
#include "OrbeXP.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    static pair<int,int> getRandomPos(Player& player, int first_circle, int second_circle);

    QGraphicsScene * scene;
    QTimer *gameTimer;
    Player* player;
    HUD *hud;
    Map *map;
    Menu *menu;
    Vague *vague;

    //pause menu
    QPushButton *buttonResume;
    QPushButton *buttonBackToMenu;
    QPushButton *buttonExit;
    vector<QGraphicsProxyWidget*> proxis;

    //ajout
    int nbObjetPossible;
    std::map<string, string> mapUpgradeNoms;
    vector<Upgrade*> vecUpgrades; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu
    vector<Upgrade*> vecUpJoueur; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu
    vector<Upgrade*> vecUpPasJoueur; //renvoie un vecteur d'une instance de chaque upgrade dispo dans le jeu
    bool inGame; //true si le jeu peut etre mis en pause
    bool pauseMenuOut; //true si le menu de pause est affiché

    static double calculDistance(pair<double, double>, pair<double, double>);
    void afficherChoix();
    void makeNewGame(QString choixPerso);
    void showMenu();
    void keyPressEvent(QKeyEvent *event) override;
    void buildPauseMenu();

public slots:
    void handleSignalFromPlayer();
    void handleSignalFinChoix(Upgrade *upgrade);
    void handleSignalPlay(QString name);
    void handleSignalExit();
    void handleResumeClicked();
    void handleBackToMenuClicked();
    void handleExitClicked();
// fin ajout
};

#endif // GAME_H
