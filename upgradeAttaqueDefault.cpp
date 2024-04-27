#include "upgradeAttaqueDefault.h"
#include "Fonctions.h"
#include "Monstre.h"
#include <QMovie>
#include <QLabel>

QString upgradeAttaqueDefault::name = QString("Epee");
QString upgradeAttaqueDefault::description = QString("Coup d'epee");
QString upgradeAttaqueDefault::imageIcone = QString(":/graphics/UpgradeImages/Epee.png");
double upgradeAttaqueDefault::cooldown = 500;
double upgradeAttaqueDefault::animationDuration = 300;

upgradeAttaqueDefault::upgradeAttaqueDefault(Player *player)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone)
{
}

Fonctions fonctions;

void upgradeAttaqueDefault::effect(){

    int side = (player->getOrientation()) ? -1 : 1;

    int width = 120 * side;
    int height = 50;

    int lvl = this->getLevel() * 5;
    // parcourir tous les monstres
    for(const auto& monstre : Monstre::vectMonstre){
        // vérifier si le monstre est dans la zone de dégâts
        if(monstre->pos().x()  >= player->pos().x() && monstre->pos().x()<= player->pos().x() + width || monstre->pos().x() <= player->pos().x() && monstre->pos().x() > player->pos().x() + width)
            if(monstre->pos().y() <= player->pos().y() + (height / 2) && monstre->pos().y() >= player->pos().y() - (height /2)){
                monstre->takeDamage(20 + lvl);
            }
    }
    affichage();
}
// connecter le timer au gameTimer

void upgradeAttaqueDefault::affichage(){
    //afficher une image
    QGraphicsPixmapItem* attackEffect = new QGraphicsPixmapItem(QPixmap(this->getImageIcone()));

    attackEffect->setScale(4);
    int taille_images = 32;
    //calculer le centre du player et de l'image de l'attaque
    pair<double,double> player_centre = make_pair(player->pos().x() + taille_images / 2, player->pos().y() - taille_images / 2);

    if(player->getOrientation() == 1){
        attackEffect->setRotation(-90);
        attackEffect->setPos(player_centre.first - 120, player_centre.second + 70);

    } else {
        attackEffect->setRotation(90);
        attackEffect->setPos(player_centre.first + 120 , player_centre.second);
    }

    player->scene()->addItem(attackEffect);
    //supprimer l'image

    //supprimer l'image
    QTimer *imageRemovalTimer = new QTimer(this);
    connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect, imageRemovalTimer]() {
        player->scene()->removeItem(attackEffect);
        delete attackEffect;
        imageRemovalTimer->deleteLater();
    });
    imageRemovalTimer->start(this->getAnimationDuration());
}
