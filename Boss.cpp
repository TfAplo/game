#include "Boss.h"


#include <QTimer>

Boss::Boss(pair<double,double> position, double hp,double speed,double dmg,QTimer *gameTimer, Player *player, QGraphicsScene *scene, QGraphicsItem *parent)
    : Monstre(false, "", position, hp, hp , speed , dmg, gameTimer, player, scene, parent),position(position) {

    // Charger la texture du Monstre
    QPixmap bossTexture(":/graphics/Tiles/tile_0122.png");
    setPixmap(bossTexture.scaled(45, 45)); // Ajuster la taille de la texture du joueur

    setPos(position.first, position.second);

    connect(gameTimer, &QTimer::timeout, this, &Monstre::move);

    elapsed=0;


}

pair<double, double> Boss::getPosition() const
{
    return position;
}

QTimer *Boss::getGameTimer() const
{
    return gameTimer;
}

Player *Boss::getPlayer() const
{
    return player;
}

QGraphicsScene *Boss::getScene() const
{
    return scene;
}
