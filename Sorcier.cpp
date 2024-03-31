#include "Sorcier.h"

#include <QTimer>

Sorcier::Sorcier(bool initNoCreation,pair<double,double> position, QTimer *gameTimer, Player *player, QGraphicsScene *scene, QGraphicsItem *parent)
    : Monstre(initNoCreation,true, "", position, 100., 100., 1., 10., gameTimer, player, scene, parent),position(position) {
    if (!initNoCreation){
        // Charger la texture du Monstre
        QPixmap ghostTexture(":/graphics/Tiles/tile_0111.png");
        setPixmap(ghostTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur

        QPointF positionJoueur = player->getPosition();

        setPos(position.first, position.second);

        connect(gameTimer, &QTimer::timeout, this, &Monstre::move);

        elapsed=0;
    }

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
