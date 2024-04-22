#include "upgradeAttaqueShield.h"
#include <QTimer>
#include <iostream>
using namespace std;

upgradeAttaqueShield::upgradeAttaqueShield(QString name,QString description,QString imageIcone,QString imageAnimation,double cooldown,double animationDuration,double widthAttaque, double heightAttaque,QGraphicsItem *parent)
    : upgradeAttaqueMelee(name,description,imageIcone,imageAnimation,cooldown,animationDuration,widthAttaque,heightAttaque,parent){
    this->actif = false;
}



// creer un shield autour du joueur
void upgradeAttaqueShield::defaultAttack(Player& player, vector<Monstre*> monstres){
    // recuperer la position du joueur
    QPointF playerCenter = player.pos();

    //calculer une zone en cercle autour du joueur en fonction du level
    int taille = this->getWidth() + (10 * this->getLevel()) / 100;

    for(const auto& monstre : monstres){
        // si la position du monstre est dans le cercle on lui inflige des degats
        QPointF monsterPos = monstre->pos();

        double distance = sqrt(pow(monsterPos.x() - playerCenter.x(), 2) + pow(monsterPos.y() - playerCenter.y(), 2));

        if(distance <= taille){
            int dmg = 15;
            monstre->takeDamage(dmg);
        }

    }

}

void upgradeAttaqueShield::affichage(Player& player,upgradeAttaque& upgrade,QGraphicsScene& scene){
    /*
    // Récupérer la position du joueur
    QPointF playerCenter = player.pos();

    // Calculer la taille du bouclier en fonction du niveau
    int shieldSize = this->getWidth() + (10 * this->getLevel()) / 100 + 20;

    // Créer un QGraphicsEllipseItem pour représenter le cercle du bouclier
    QGraphicsEllipseItem* shieldCircle = new QGraphicsEllipseItem(
        playerCenter.x() - (shieldSize / 2 -16),   // Position X du centre du cercle
        playerCenter.y() - (shieldSize / 2 - 16),   // Position Y du centre du cercle
        shieldSize,                          // Largeur du cercle
        shieldSize                           // Hauteur du cercle (même que la largeur pour un cercle)
        );

    // Définir la couleur et le style du cercle (par exemple, couleur bleue)
    QColor shieldColor = QColor(0, 0, 255, 128); // Bleu semi-transparent (RGBA)
    QPen pen(shieldColor);  // Couleur de la bordure du cercle (bleu)
    QBrush brush(shieldColor);  // Couleur de remplissage du cercle (bleu)

    shieldCircle->setPen(pen);       // Appliquer la couleur de la bordure
    shieldCircle->setBrush(brush);   // Appliquer la couleur de remplissage

    // Ajouter le cercle du bouclier à la scène
    scene.addItem(shieldCircle);
    */
}
