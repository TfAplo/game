#include "upgradeAttaqueArc.h"
#include "Monstre.h"
#include "Fleche.h"
#include <QMovie>
#include <QLabel>

QString upgradeAttaqueArc::name = QString("Arc");
QString upgradeAttaqueArc::description = QString("Inflige des degats important à longue distance");
QString upgradeAttaqueArc::imageIcone = QString(":/graphics/UpgradeImages/Arc.png");
double upgradeAttaqueArc::cooldown = 2500;
double upgradeAttaqueArc::animationDuration = 2500;

upgradeAttaqueArc::upgradeAttaqueArc(Player* player, QTimer *gameTimer)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone), gameTimer(gameTimer) {
    setActif();
}

double upgradeAttaqueArc::calculDistance(const QPointF &point1, const QPointF &point2) {
    double dx = point2.x() - point1.x();
    double dy = point2.y() - point1.y();
    return std::sqrt(dx * dx + dy * dy);
}

void upgradeAttaqueArc::effect() {
    // Trouver le monstre le plus proche du joueur
    int lvl = this->getLevel() * 10;
    Monstre *targetMonster = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (Monstre *monster : Monstre::vectMonstre) {
        double distance = calculDistance(player->pos(), monster->pos());
        if (distance < minDistance) {
            minDistance = distance;
            targetMonster = monster;
        }
    }

    // Si un monstre est trouvé, lancer une flèche
    if (targetMonster) {
        Fleche *fleche = new Fleche(player, targetMonster, player->scene(), gameTimer, 40 + lvl, ":/graphics/UpgradeImages/Fleche.png");
        player->scene()->addItem(fleche);
    }

    // Affichage de l'attaque
    //affichage();
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
