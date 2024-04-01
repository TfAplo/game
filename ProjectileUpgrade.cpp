#include "ProjectileUpgrade.h"

ProjectileUpgrade::ProjectileUpgrade(QString name, QString description, QString pathImage,int level, double cooldown, double animationDuration, double dmg, bool autoAim, double speed, pair<double,double> position) :
 Upgrades(name, description, pathImage,level, cooldown, animationDuration, dmg){
    this->autoAim = autoAim;
    this->speed = speed;
    this->position = position;
}


// tire un projectile dans le direction du monstre le plus proche si auto sinon direction du joueur
void ProjectileUpgrade::defaultAttack(Player& player, vector<Monstre*> monstres){

    if(this->autoAim){
        //  auto

        double closeDistance = sqrt(pow(player.pos().x() - monstres[0]->pos().x(), 2) + pow(player.pos().y() - monstres[0]->pos().y(), 2));
        Monstre* closer = monstres[0];

         // recuperer le monstre le plus proche a l'instant T
        for(const auto& monstre : monstres){
            // calcule de la distance
            double distance = sqrt(pow(player.pos().x() - monstre->pos().x(), 2) + pow(player.pos().y() - monstre->pos().y(), 2));
            if(distance < closeDistance){
                closeDistance = distance;
                closer = monstre;
            }
        }

        // envoyer le projectile dans sa direction


    } else {

    }
}
