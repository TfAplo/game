#include "upgradeAttaqueHache.h"
#include "Monstre.h"
#include <QMovie>
#include <QLabel>

QString upgradeAttaqueHache::name = QString("Hache");
QString upgradeAttaqueHache::description = QString("Inflige de lourdes attaques des deux cotes du personnage");
QString upgradeAttaqueHache::imageIcone = QString(":/graphics/UpgradeImages/Hache.png");
double upgradeAttaqueHache::cooldown = 1500;
double upgradeAttaqueHache::animationDuration = 350;

upgradeAttaqueHache::upgradeAttaqueHache(Player *player,QTimer* gameTimer)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone, gameTimer){
}

void upgradeAttaqueHache::effect(){

    int width = 80;
    int height = 85;

    int lvl = this->getLevel() * 5;
    // parcourir tous les monstres
    for(const auto& monstre : Monstre::vectMonstre){
        // vérifier si le monstre est dans la zone de dégâts de droite
        if(monstre->pos().x()  >= player->pos().x() && monstre->pos().x()<= player->pos().x() + width || monstre->pos().x() <= player->pos().x() && monstre->pos().x() > player->pos().x() + width)
            if(monstre->pos().y() <= player->pos().y() + (height / 2) && monstre->pos().y() >= player->pos().y() - (height /2)){
                monstre->takeDamage(35 + lvl);
            }
        // vérifier si le monstre est dans la zone de dégâts de gauche
        if(monstre->pos().x() <= player->pos().x() && monstre->pos().x() >= player->pos().x() - width || monstre->pos().x() >= player->pos().x() && monstre->pos().x() < player->pos().x() - width)
            if(monstre->pos().y() >= player->pos().y() - (height / 2) && monstre->pos().y() <= player->pos().y() + (height /2)){
                monstre->takeDamage(35 + lvl);
            }
    }
    affichage();
}
// connecter le timer au gameTimer

void upgradeAttaqueHache::affichage(){
    //afficher une image
    QGraphicsPixmapItem* attackEffect = new QGraphicsPixmapItem(QPixmap(imageIcone));
    QGraphicsPixmapItem* attackEffect2 = new QGraphicsPixmapItem(QPixmap(imageIcone));

    attackEffect->setScale(3.5);
    attackEffect2->setScale(3.5);
    int taille_images = 32;
    //calculer le centre du player et de l'image de l'attaque
    pair<double,double> player_centre = make_pair(player->pos().x() + taille_images / 2, player->pos().y() - taille_images / 2);

    attackEffect->setRotation(-90);
    attackEffect->setPos(player_centre.first - 72, player_centre.second + 63);

    attackEffect2->setRotation(90);
    attackEffect2->setPos(player_centre.first + 70 , player_centre.second + 7);

    player->scene()->addItem(attackEffect);
    player->scene()->addItem(attackEffect2);

    //supprimer l'image
    QTimer *imageRemovalTimer = new QTimer(this);
    connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect, imageRemovalTimer]() {
        player->scene()->removeItem(attackEffect);
        delete attackEffect;
        imageRemovalTimer->deleteLater();
    });
    imageRemovalTimer->start(animationDuration);
    QTimer *imageRemovalTimer2 = new QTimer(this);
    connect(imageRemovalTimer, &QTimer::timeout, [this, attackEffect2, imageRemovalTimer]() {
        player->scene()->removeItem(attackEffect2);
        delete attackEffect2;
        imageRemovalTimer->deleteLater();
    });
    imageRemovalTimer->start(animationDuration);
}
