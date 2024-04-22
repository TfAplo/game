#include "Player.h"
#include <iostream>
#include <QTimer>
#include <QKeyEvent>

//ajout
#include "Game.h"
#include "OrbeXP.h"
#include <vector>
//fin ajout

using namespace std;


Player::Player(QString& image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, double xp, double limiteXP,QGraphicsItem *parent) :
    Personnage(image,position,current_hp,max_hp,speed,dmg,parent), xp(xp), limiteXP(limiteXP), niveau(0)
{
    leftOriented =movingLeft = movingRight = movingUp = movingDown = false;
    // Charger la texture du joueur
    playerTextureRight = QPixmap(image);
    playerTextureLeft = playerTextureRight.transformed(QTransform().scale(-1, 1));
    setPixmap(playerTextureRight.scaled(32, 32)); // Ajuster la taille de la texture du joueur

    // Positionner le joueur
    setPos(position.first, position.second);

    hpBar = new HPBar(32, 5, this); // taille de la barre de santé (modifiable)
    hpBar->setPos(0, 32); // position relative à l'objet Personnage

    xpBar = new XPBar(100, 30);
    xpBar->setZValue(2);
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

//ajout

void Player::recupXP() {
    // a supp car test
    QPointF posJ = this->pos();
    pair<double, double> posJoueur = make_pair(posJ.x(), posJ.y());

    for (auto it = OrbeXP::vecOrbeXP.begin(); it != OrbeXP::vecOrbeXP.end(); ++it) {
        OrbeXP* orbeXP = *it;
        pair<double, double> pos = orbeXP->getPos();
        if (Game::calculDistance(pos, posJoueur) <= 30) {
            // ajoute l'orbe dans vecASupp
            // vecASupp.push_back(orbeXP); // Je commente cette ligne car vous n'utilisez pas vecASupp
            // ajouter l'XP au joueur
            this->ajouterXP(orbeXP->getXP());
            cout << "Xp augmentee : " << xp << endl;
            delete orbeXP; // Supprime l'objet orbeXP
            OrbeXP::vecOrbeXP.erase(it); // Supprime l'élément du vecteur
            --it; // Décrémente l'itérateur pour rester sur le bon élément après l'effacement
        }
    }

    if (this->xp >= this->limiteXP) {
        this->augmenterNiveau(1);
    }
}

void Player::augmenterNiveau(double niv) {
    this->niveau += niv;
    this->xp = this->xp - this->limiteXP;
    this->limiteXP *= 1.5;

    cout << "Niveau augmente : " << this->getNiveau() << endl;
    //Game::afficherChoix();
    emit signalToGame();
}

void Player::ajouterXP(double xp) {
    this->xp += xp;
}

double Player::getNiveau() {
    return niveau;
}

void Player::setNiveau(double niveau) {
    this->niveau = niveau;
}

//fin ajout


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

bool Player::getOrientation() const{
    return this->leftOriented;
}

vector<Upgrade *> Player::getUpgrades()
{
    return upgrades;
}

// AJOUT VALENTIN

void Player::setSpeed(double s){
    this->speed = s;
}

double Player::getSpeed() const{
    return this->speed;
}

void Player::setMaxHp(double hp){
    this->max_hp = hp;
}

double Player::getMaxHp() const {
    return this->max_hp;
}

void Player::setCurrentHp(double hp){
    if(hp <= this->getMaxHp()){
        this->current_hp = hp;
    } else {
        this->current_hp = this->getMaxHp();
    }

}
