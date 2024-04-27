#include "Sorcier.h"

#include <QTimer>

Sorcier::Sorcier(pair<double,double> position,double hp,double speed,double dmg, QTimer *gameTimer, Player *player, QGraphicsScene *scene, QGraphicsItem *parent)
    : Monstre(true, "", position, hp, hp, speed, dmg, gameTimer, player, scene, parent),position(position) {

    // Charger la texture du Monstre
    QPixmap sorcierTexture(":/graphics/Tiles/tile_0111.png");
    setPixmap(sorcierTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur

    QPointF positionJoueur = player->getPosition();

    setPos(position.first, position.second);

    connect(gameTimer, &QTimer::timeout, this, &Monstre::move);

    elapsed=0;


}

pair<double, double> Sorcier::getPosition() const
{
    return position;
}

QTimer *Sorcier::getGameTimer() const
{
    return gameTimer;
}

Player *Sorcier::getPlayer() const
{
    return player;
}

QGraphicsScene *Sorcier::getScene() const
{
    return scene;
}
