#include "Boss.h"


#include <QTimer>

Boss::Boss(bool initNoCreation,pair<double,double> position, QTimer *gameTimer, Player *player, QGraphicsScene *scene, QGraphicsItem *parent)
    : Monstre(initNoCreation,false, "", position, 100., 100., 1., 30., gameTimer, player, scene, parent),position(position) {
    if (!initNoCreation){
        // Charger la texture du Monstre
        QPixmap ghostTexture(":/graphics/Tiles/tile_0122.png");
        setPixmap(ghostTexture.scaled(45, 45)); // Ajuster la taille de la texture du joueur

        setPos(position.first, position.second);

        connect(gameTimer, &QTimer::timeout, this, &Monstre::move);

        elapsed=0;
    }

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
