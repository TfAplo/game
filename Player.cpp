#include "Player.h"
#include <iostream>
#include <QTimer>
#include <QKeyEvent>

using namespace std;


Player::Player(QString& image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, double xp,QGraphicsItem *parent) :
    Personnage(image,position,current_hp,max_hp,speed,dmg,parent), xp(xp)
{
    movingLeft = movingRight = movingUp = movingDown = false;
    // Charger la texture du joueur
    QPixmap playerTexture(":/graphics/Tiles/tile_0084.png");
    setPixmap(playerTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur

    // Positionner le joueur
    setPos(position.first, position.second);
}

void Player::details()
{

    Personnage::details();
    cout << "xp : " << this->xp << endl;
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    // Annuler le marquage de la direction lorsque la touche est relâchée
    switch (event->key()) {
    case Qt::Key_Left:
        movingLeft = false;
        break;
    case Qt::Key_Right:
        movingRight = false;
        break;
    case Qt::Key_Up:
        movingUp = false;
        break;
    case Qt::Key_Down:
        movingDown = false;
        break;
    default:
        break;
    }
}


void Player::keyPressEvent(QKeyEvent *event)
{
    // Marquer la direction dans laquelle le joueur souhaite se déplacer
    switch (event->key()) {
    case Qt::Key_Left:
        movingLeft = true;
        break;
    case Qt::Key_Right:
        movingRight = true;
        break;
    case Qt::Key_Up:
        movingUp = true;
        break;
    case Qt::Key_Down:
        movingDown = true;
        break;
    default:
        break;
    }
}

void Player::move()
{
    // Déplacer le joueur en fonction des directions marquées
    qreal dx = 0, dy = 0;
    if (movingLeft) dx -= speed;
    if (movingRight) dx += speed;
    if (movingUp) dy -= speed;
    if (movingDown) dy += speed;
    setPos(mapToParent(dx, dy)); // Déplacer le joueur par rapport à sa position actuelle
}
