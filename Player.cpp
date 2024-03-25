#include "Player.h"
#include <iostream>
#include <QTimer>
#include <QKeyEvent>
using namespace std;


Player::Player(string image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, double xp,QGraphicsItem *parent) :
    Personnage(image,position,current_hp,max_hp,speed,dmg,parent), xp(xp),limiteXP(100), niveau(0)
{
    leftOriented =movingLeft = movingRight = movingUp = movingDown = false;
    // Charger la texture du joueur
    playerTextureRight = QPixmap(QString::fromStdString(image));
    playerTextureLeft = playerTextureRight.transformed(QTransform().scale(-1, 1));
    setPixmap(playerTextureRight.scaled(32, 32)); // Ajuster la taille de la texture du joueur

    // Positionner le joueur
    setPos(position.first, position.second);

    hpBar = new HPBar(32, 5, this); // taille de la barre de santé (modifiable)
    hpBar->setPos(0, 32); // position relative à l'objet Personnage

    xpBar = new XPBar(100, 30);
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
    case Qt::Key_Q:
    case Qt::Key_Left:
        movingLeft = false;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        movingRight = false;
        break;
    case Qt::Key_Z:
    case Qt::Key_Up:
        movingUp = false;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        movingDown = false;
        break;
    default:
        break;
    }
}

void Player::updateHPBar()
{
    hpBar->updateBar(current_hp, max_hp);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    // Marquer la direction dans laquelle le joueur souhaite se déplacer
    switch (event->key()) {
    case Qt::Key_Q:
    case Qt::Key_Left:
        movingLeft = true;
        updateOrientation(true);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        movingRight = true;
        updateOrientation(false);
        break;
    case Qt::Key_Z:
    case Qt::Key_Up:
        movingUp = true;
        break;
    case Qt::Key_S:
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

void Player::takeDamage(double dmg){
    Personnage::takeDamage(dmg);
    updateHPBar();
}

XPBar *Player::getXPBar()
{
    return xpBar;
}

void Player::setXP(double xp) {
    this->xp = xp;
}

double Player::getXP(){
    return this->xp;
}

double Player::getlimitXP(){
    return this->limiteXP;
}

double Player::getNiveau()
{
    return this->niveau;
}

void Player::ajouterXP(double xp) {
    this->xp += xp;
}

void Player::updateOrientation(bool movesLeft)
{
    //change l'orientation de la texture du player
    if (movesLeft && !leftOriented){
        leftOriented = true;
        setPixmap(playerTextureLeft);
        setPixmap(playerTextureLeft.scaled(32, 32));
    }else if(!movesLeft && leftOriented){
        leftOriented = false;
        setPixmap(playerTextureRight);
        setPixmap(playerTextureRight.scaled(32, 32));
    }

}

vector<Upgrade *> Player::getUpgrades()
{
    return upgrades;
}
