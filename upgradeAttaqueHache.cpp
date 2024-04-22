#include "upgradeAttaqueHache.h"
#include <QTimer>

upgradeAttaqueHache::upgradeAttaqueHache(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,double widthAttaque, double heightAttaque,QGraphicsItem *parent)
    : upgradeAttaque(name,description,imageIcone,imageAnimation,cooldown,animationDuration, parent)
{
    this->widthAttaque = widthAttaque;
    this->heightAttaque = heightAttaque;
}

double upgradeAttaqueHache::getWidth() const{
    return this->widthAttaque;
}
double upgradeAttaqueHache::getHeight() const{
    return this->heightAttaque;
}


void upgradeAttaqueHache::defaultAttack(Player& player, vector<Monstre*> monstres){

    int side = (player.getOrientation()) ? -1 : 1;

    int width = this->widthAttaque * side;
    int height = this->heightAttaque;

    // parcourir tous les monstres
    for(const auto& monstre : monstres){
        // vérifier si le monstre est dans la zone de dégâts de droite
        if(monstre->pos().x()  >= player.pos().x() && monstre->pos().x()<= player.pos().x() + width || monstre->pos().x() <= player.pos().x() && monstre->pos().x() > player.pos().x() + width)
            if(monstre->pos().y() <= player.pos().y() + (height / 2) && monstre->pos().y() >= player.pos().y() - (height /2)){
                monstre->takeDamage(100);
            }
        // vérifier si le monstre est dans la zone de dégâts de gauche
        if(monstre->pos().x() <= player.pos().x() && monstre->pos().x() >= player.pos().x() - width || monstre->pos().x() >= player.pos().x() && monstre->pos().x() < player.pos().x() - width)
            if(monstre->pos().y() >= player.pos().y() - (height / 2) && monstre->pos().y() <= player.pos().y() + (height /2)){
                monstre->takeDamage(100);
            }
    }

}



void upgradeAttaqueHache::affichage(Player& player,upgradeAttaque& upgrade, QGraphicsScene& scene){
    //afficher une image
    QGraphicsPixmapItem* attackEffect = new QGraphicsPixmapItem(QPixmap(upgrade.getImageIcone()));
    QGraphicsPixmapItem* attackEffect2 = new QGraphicsPixmapItem(QPixmap(upgrade.getImageIcone()));

    attackEffect->setScale(3.5);
    attackEffect2->setScale(3.5);
    int taille_images = 32;
    //calculer le centre du player et de l'image de l'attaque
    pair<double,double> player_centre = make_pair(player.pos().x() + taille_images / 2, player.pos().y() - taille_images / 2);

    attackEffect->setRotation(-90);
    attackEffect->setPos(player_centre.first - 72, player_centre.second + 63);

    attackEffect2->setRotation(90);
    attackEffect2->setPos(player_centre.first + 70 , player_centre.second + 7);

    scene.addItem(attackEffect);
    scene.addItem(attackEffect2);

    //supprimer l'image
    QTimer *imageRemovalTimer = new QTimer(this);
    connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect, imageRemovalTimer, &scene]() {
        scene.removeItem(attackEffect);
        delete attackEffect;
        imageRemovalTimer->deleteLater();
    });
    imageRemovalTimer->start(upgrade.getAnimationDuration());
    QTimer *imageRemovalTimer2 = new QTimer(this);
    connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect2, imageRemovalTimer, &scene]() {
        scene.removeItem(attackEffect2);
        delete attackEffect2;
        imageRemovalTimer->deleteLater();
    });
    imageRemovalTimer->start(upgrade.getAnimationDuration());
}
