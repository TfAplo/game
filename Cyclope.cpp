#include "Cyclope.h"

#include <QTimer>

Cyclope::Cyclope(pair<double,double> position,double hp,double speed,double dmg, QTimer *gameTimer, Player *player, QGraphicsScene *scene, QGraphicsItem *parent)
    : Monstre(false, "", position, hp, hp, speed, dmg, gameTimer, player, scene, parent),position(position) {

    // Charger la texture du Monstre
    QPixmap cyclopeTexture(":/graphics/Tiles/tile_0109.png");
    setPixmap(cyclopeTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur

    setPos(position.first, position.second);

    connect(gameTimer, &QTimer::timeout, this, &Monstre::move);

    elapsed=0;


}

pair<double, double> Cyclope::getPosition() const
{
    return position;
}

QTimer *Cyclope::getGameTimer() const
{
    return gameTimer;
}

Player *Cyclope::getPlayer() const
{
    return player;
}

QGraphicsScene *Cyclope::getScene() const
{
    return scene;
}
