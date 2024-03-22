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


Player::Player(string image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, double xp,QGraphicsItem *parent) :
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

//ajout

void Player::recupXP() {
    // a supp car test
    vector<OrbeXP*> vecOrbeXP;
    OrbeXP* orbe1 = new OrbeXP("Orbe", make_pair(200, 200));
    vecOrbeXP.push_back(orbe1);
    for (OrbeXP* orbeXP : vecOrbeXP) {
        pair<double, double> pos = orbeXP->getPos(); //orbe.getPos();
        if (Game::calculDistance(pos, this->getPos()) <= 5) {
            //ajouter l'XP au joueur
            this->ajouterXP(orbeXP->getXP());
            //supprimer l'orbeXP
            delete orbeXP;
        }
    }
    if (this->xp >= this->limiteXP) {
        this->augmenterNiveau(1);
    }
}

void Player::augmenterNiveau(double niveau) {
    this->niveau += niveau;
    this->xp = this->xp - this->limiteXP;
    this->limiteXP *= 1.5;

    //Game::afficherChoix(); // comment appeler afficherChoix de Game dans Player (passage en argument, ou alors attribut Game* game;)

}

void Player::setXP(double xp) {
    this->xp = xp;
}

void Player::ajouterXP(double xp) {
    this->xp += xp;
}

void Player::setNiveau(double niveau) {
    this->niveau = niveau;
}

//fin ajout

