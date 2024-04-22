#include "upgradeAttaqueArc.h"
#include <QTimer>

upgradeAttaqueArc::upgradeAttaqueArc(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,double widthAttaque, double heightAttaque,QGraphicsItem *parent)
    : upgradeAttaque(name,description,imageIcone,imageAnimation,cooldown,animationDuration, parent)
{
    this->widthAttaque = widthAttaque;
    this->heightAttaque = heightAttaque;
}

void upgradeAttaqueArc::defaultAttack(Player& player, vector<Monstre*> monstres){

}

void upgradeAttaqueArc::affichage(Player& player,upgradeAttaque& upgrade, QGraphicsScene& scene){
    //afficher une image
    QGraphicsPixmapItem* attackEffect = new QGraphicsPixmapItem(QPixmap(upgrade.getImageIcone()));

    attackEffect->setScale(1.5);
    int taille_images = 32;
    //calculer le centre du player et de l'image de l'attaque
    pair<double,double> player_centre = make_pair(player.pos().x() + taille_images / 2, player.pos().y() - taille_images / 2);

    if(player.getOrientation() == 1){
        attackEffect->setRotation(180);
        attackEffect->setPos(player_centre.first - 9, player_centre.second + 49);

    } else {
        attackEffect->setRotation(0);
        attackEffect->setPos(player_centre.first + 10, player_centre.second + 24);

    }

    scene.addItem(attackEffect);
    //supprimer l'image

    //supprimer l'image
    QTimer *imageRemovalTimer = new QTimer(this);
    connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect, imageRemovalTimer, &scene]() {
        scene.removeItem(attackEffect);
        delete attackEffect;
        imageRemovalTimer->deleteLater();
    });
    imageRemovalTimer->start(upgrade.getAnimationDuration());

}
