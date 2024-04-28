#include "Projectile.h"
#include <QTimer>
#include <QGraphicsScene>

using namespace std;

Projectile::Projectile(Player *player,QGraphicsScene *scene,pair<double, double> position,QTimer *gameTimer,pair<double, double> positionP,double dmg, QString Texture)
    : player(player), scene(scene),positionM(position),gameTimer(gameTimer),positionP(positionP),dmg(dmg){

    QPixmap playerTexture(Texture);
    setPixmap(playerTexture.scaled(20, 20)); // Ajuster la taille de la texture du joueur
    setPos(positionM.first, positionM.second);


    QTimer::singleShot(5000, this, &Projectile::destroyProjectile);
    connect(gameTimer, &QTimer::timeout, this, &Projectile::move);


}

void Projectile::move(){
    // Calculer la direction initiale du projectile lorsqu'il est tiré
    qreal directionX = positionP.first - positionM.first;
    qreal directionY = positionP.second - positionM.second;

    // Calculer la longueur de la direction initiale
    qreal length = qSqrt(directionX * directionX + directionY * directionY);

    // Normaliser la direction initiale
    if (length > 0.0) {
        directionX /= length;
        directionY /= length;
    }

    qreal speed = 3.; // Vitesse du projectile

    // Déplacer le projectile dans la direction initiale
    qreal dx = directionX * speed;
    qreal dy = directionY * speed;
    setPos(mapToParent(dx, dy));

    qreal distanceToPlayer = qSqrt(pow(player->x() - x(), 2) + pow(player->y() - y(), 2));
    if (distanceToPlayer < 20) {
        player->takeDamage(dmg);
        destroyProjectile();
    }
}

void Projectile::destroyProjectile() {
    scene->removeItem(this); // Supprimer le projectile de la scène
    delete this; // Libérer la mémoire allouée pour le projectile
}
