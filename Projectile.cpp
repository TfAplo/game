#include "Projectile.h"
#include <QTimer>

using namespace std;

Projectile::Projectile(Player *player,QGraphicsScene * scene,pair<double, double> position,QTimer *gameTimer,pair<double, double> positionP) : player(player), scene(scene),positionM(position),gameTimer(gameTimer),positionP(positionP){


    QPixmap playerTexture(":/graphics/Tiles/tile_0102.png");
    setPixmap(playerTexture.scaled(20, 20)); // Ajuster la taille de la texture du joueur
    setPos(positionM.first, positionM.second);



    connect(gameTimer, &QTimer::timeout, this, &Projectile::move);


}

void Projectile::move(){
    // Obtenir les coordonnées actuelles projectile
   /* qreal positionX = this->x();
    qreal positionY = this->y();

    // Obtenir les coordonnées du player
    qreal positionPlayerX = positionM.first;
    qreal positionPlayerY=positionM.second;



    qreal directionVersJoueurX = positionPlayerX - positionX;
    qreal directionVersJoueurY = positionPlayerY - positionY;

    // Normaliser la direction vers le joueur
    qreal length = qSqrt(directionVersJoueurX * directionVersJoueurX + directionVersJoueurY * directionVersJoueurY);
    if (length > 0.0) {
        directionVersJoueurX /= length;
        directionVersJoueurY /= length;
    }

    // Calculer le déplacement nécessaire pour se rapprocher de la cible
    qreal dx = directionVersJoueurX * 1.5;
    qreal dy = directionVersJoueurY * 1.5;

    setPos(mapToParent(dx, dy));*/



    // Stocker la direction vers le joueur au moment du tir du projectile
    qreal playerPositionX = positionP.first;
    qreal playerPositionY = positionP.second;
    qreal directionX = playerPositionX - x();
    qreal directionY = playerPositionY - y();

    // Normaliser la direction
    qreal length = qSqrt(directionX * directionX + directionY * directionY);
    if (length > 0.0) {
        directionX /= length;
        directionY /= length;
    }
    qreal dx = directionX * 1.4;
    qreal dy = directionY * 1.4;
    setPos(mapToParent(dx, dy));

}
