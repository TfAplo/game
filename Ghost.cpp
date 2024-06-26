#include "Ghost.h"
#include <QTimer>

Ghost::Ghost(pair<double,double> position,double hp, double speed, double dmg, QTimer *gameTimer, Player *player, QGraphicsScene *scene, QGraphicsItem *parent)
    : Monstre(false, "", position, hp, hp, speed, dmg, gameTimer, player, scene, parent),position(position) {

    // Charger la texture du Monstre
    QPixmap ghostTexture(":/graphics/Tiles/tile_0108.png");
    setPixmap(ghostTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur

    QPointF positionJoueur = player->getPosition();

    setPos(position.first, position.second);

    connect(gameTimer, &QTimer::timeout, this, &Monstre::move);

    elapsed=0;


}

pair<double, double> Ghost::getPosition() const
{
    return position;
}

QTimer *Ghost::getGameTimer() const
{
    return gameTimer;
}

Player *Ghost::getPlayer() const
{
    return player;
}

QGraphicsScene *Ghost::getScene() const
{
    return scene;
}
