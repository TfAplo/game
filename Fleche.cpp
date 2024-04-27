#include "Fleche.h"
#include "Player.h" // Assure-toi que Player est inclus et défini correctement

Fleche::Fleche(Player *player, Monstre *targetMonster, QGraphicsScene *scene, QTimer *gameTimer, double dmg, const QString &texturePath, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), player(player), targetMonster(targetMonster), scene(scene), gameTimer(gameTimer), dmg(dmg)
{
    QPixmap flecheTexture(texturePath);
    setPixmap(flecheTexture.scaled(20, 20)); // Ajuste la taille de la texture de la flèche
    setPos(player->pos()); // Positionne la flèche au joueur

    connect(gameTimer, &QTimer::timeout, this, &Fleche::move);
}

Fleche::~Fleche()
{
    // Supprimer la flèche de la scène lorsqu'elle est détruite
    scene->removeItem(this);
}

void Fleche::move()
{
    // Calculer la direction de la flèche vers le monstre
    qreal directionX = targetMonster->pos().x() - pos().x();
    qreal directionY = targetMonster->pos().y() - pos().y();

    // Calculer la longueur de la direction
    qreal length = qSqrt(directionX * directionX + directionY * directionY);

    // Normaliser la direction
    if (length > 0.0) {
        directionX /= length;
        directionY /= length;
    }

    qreal speed = 5.0; // Vitesse de la flèche

    // Déplacer la flèche dans la direction
    qreal dx = directionX * speed;
    qreal dy = directionY * speed;
    setPos(mapToParent(dx, dy));

    // Vérifier si la flèche touche le monstre
    qreal distanceToMonster = qSqrt(qPow(targetMonster->pos().x() - pos().x(), 2) + qPow(targetMonster->pos().y() - pos().y(), 2));
    if (distanceToMonster < 20) {
        targetMonster->takeDamage(dmg);
        deleteLater(); // Supprimer la flèche après avoir touché le monstre
    }
}
