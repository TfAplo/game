#include "upgradeAttaqueMelee.h"
#include <QTimer>

upgradeAttaqueMelee::upgradeAttaqueMelee(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,double widthAttaque, double heightAttaque,QGraphicsItem *parent)
    : upgradeAttaque(name,description,imageIcone,imageAnimation,cooldown,animationDuration, parent)
{
    this->widthAttaque = widthAttaque;
    this->heightAttaque = heightAttaque;
}

double upgradeAttaqueMelee::getWidth() const{
    return this->widthAttaque;
}
double upgradeAttaqueMelee::getHeight() const{
    return this->heightAttaque;
}


void upgradeAttaqueMelee::defaultAttack(Player& player, vector<Monstre*> monstres){

    int side = (player.getOrientation()) ? -1 : 1;

    int width = this->widthAttaque * side;
    int height = this->heightAttaque;

    // parcourir tous les monstres
    for(const auto& monstre : monstres){
        // vérifier si le monstre est dans la zone de dégâts
        if(monstre->pos().x()  >= player.pos().x() && monstre->pos().x()<= player.pos().x() + width || monstre->pos().x() <= player.pos().x() && monstre->pos().x() > player.pos().x() + width)
            if(monstre->pos().y() <= player.pos().y() + (height / 2) && monstre->pos().y() >= player.pos().y() - (height /2)){
                monstre->takeDamage(100);
            }
    }
}



void upgradeAttaqueMelee::affichage(Player& player,upgradeAttaque& upgrade, QGraphicsScene& scene){
    //afficher une image
    QGraphicsPixmapItem* attackEffect = new QGraphicsPixmapItem(QPixmap(upgrade.getImageIcone()));

    attackEffect->setScale(4);
    int taille_images = 32;
    //calculer le centre du player et de l'image de l'attaque
    pair<double,double> player_centre = make_pair(player.pos().x() + taille_images / 2, player.pos().y() - taille_images / 2);

    if(player.getOrientation() == 1){
        attackEffect->setRotation(-90);
        attackEffect->setPos(player_centre.first - 120, player_centre.second + 70);

    } else {
        attackEffect->setRotation(90);
        attackEffect->setPos(player_centre.first + 120 , player_centre.second);

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
