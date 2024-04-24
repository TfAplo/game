#include "upgradeAttaqueArc.h"
#include "Monstre.h"
#include <QMovie>
#include <QLabel>

QString upgradeAttaqueArc::name = QString("Arc");
QString upgradeAttaqueArc::description = QString("Inflige des degats important à longue distance");
QString upgradeAttaqueArc::imageIcone = QString(":/graphics/UpgradeImages/Arc.png");
double upgradeAttaqueArc::cooldown = 0;
double upgradeAttaqueArc::animationDuration = 0;

upgradeAttaqueArc::upgradeAttaqueArc(Player *player)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone){
}


void upgradeAttaqueArc::effect(){


    affichage();
}

void upgradeAttaqueArc::affichage(){
    //afficher une image
    QGraphicsPixmapItem* attackEffect = new QGraphicsPixmapItem(QPixmap(imageIcone));

    attackEffect->setScale(1.5);
    int taille_images = 32;
    //calculer le centre du player et de l'image de l'attaque
    pair<double,double> player_centre = make_pair(player->pos().x() + taille_images / 2, player->pos().y() - taille_images / 2);

    if(player->getOrientation() == 1){
        attackEffect->setRotation(180);
        attackEffect->setPos(player_centre.first - 9, player_centre.second + 49);

    } else {
        attackEffect->setRotation(0);
        attackEffect->setPos(player_centre.first + 10, player_centre.second + 24);

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
    imageRemovalTimer->start(animationDuration);
}
