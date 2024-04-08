#include "Cyclope.h"

#include <QTimer>

Cyclope::Cyclope(bool initNoCreation,pair<double,double> position, QTimer *gameTimer, Player *player, QGraphicsScene *scene, QGraphicsItem *parent)
    : Monstre(initNoCreation,false, "", position, 100., 100., 1.5, 10., gameTimer, player, scene, parent),position(position) {
    if (!initNoCreation){
        // Charger la texture du Monstre
        QPixmap ghostTexture(":/graphics/Tiles/tile_0109.png");
        setPixmap(ghostTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur

        setPos(position.first, position.second);

        connect(gameTimer, &QTimer::timeout, this, &Monstre::move);

        elapsed=0;
    }

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
