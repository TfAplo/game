#include "upgradeAttaqueShield.h"
#include "Monstre.h"

QString upgradeAttaqueShield::name = QString("shield");
QString upgradeAttaqueShield::description = QString("Inflige des degats aux monstres trop proche de vous");
QString upgradeAttaqueShield::imageIcone = QString(":/graphics/UpgradeImages/Bouclier.png");
double upgradeAttaqueShield::cooldown = 400;
double upgradeAttaqueShield::animationDuration = 0;

upgradeAttaqueShield::upgradeAttaqueShield(Player *player,QTimer* gameTimer)
    : upgradeAttaque(name,description,imageIcone,player,cooldown,animationDuration,imageIcone,gameTimer)
{

}


void upgradeAttaqueShield::effect(){
    // recuperer la position du joueur
    QPointF playerCenter = player->pos();

    int width = 80;
    int dmg = 15 + this->getLevel() * 5;

    //calculer une zone en cercle autour du joueur en fonction du level
    int taille = width + (15 * this->getLevel()) / 100;

    for(const auto& monstre : Monstre::vectMonstre){
        // si la position du monstre est dans le cercle on lui inflige des degats
        QPointF monsterPos = monstre->pos();

        double distance = sqrt(pow(monsterPos.x() - playerCenter.x(), 2) + pow(monsterPos.y() - playerCenter.y(), 2));

        if(distance <= taille){
            monstre->takeDamage(dmg);
        }

    }
}
