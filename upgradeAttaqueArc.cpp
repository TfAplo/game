#include "upgradeAttaqueArc.h"
#include "Monstre.h"
#include "Fleche.h"
#include <QMovie>
#include <QLabel>

QString upgradeAttaqueArc::name = QString("Arc");
QString upgradeAttaqueArc::description = QString("Inflige des degats important à longue distance");
QString upgradeAttaqueArc::imageIcone = QString(":/graphics/UpgradeImages/Arc.png");
double upgradeAttaqueArc::cooldown = 500;
double upgradeAttaqueArc::animationDuration = 500;

upgradeAttaqueArc::upgradeAttaqueArc(Player* player, QTimer *gameTimer)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone, gameTimer) {
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
}

