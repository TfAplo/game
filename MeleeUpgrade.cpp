#include "MeleeUpgrade.h"

MeleeUpgrade::MeleeUpgrade(QString name, QString description,QString pathImage, int level, double cooldown, double animationDuration, double dmg, double widthRange, double heightRange) :
    Upgrades(name, description,pathImage, level, cooldown, animationDuration, dmg){
    this->widthRange = widthRange;
    this->heightRange = heightRange;
}


//met un coup dans un rayon de 5 cases devant lui sur une largeur de 3 cases
void MeleeUpgrade::defaultAttack(Player& player, vector<Monstre*> monstres){

    int side = (player.getSide()) ? -1 : 1;

    int width = this->widthRange * side;
    int height = this->heightRange;

    // parcourir tous les monstres
    for(const auto& monstre : monstres){
        // vérifier si le monstre est dans la zone de dégâts
        if(monstre->pos().x()  >= player.pos().x() && monstre->pos().x()<= player.pos().x() + width || monstre->pos().x() <= player.pos().x() && monstre->pos().x() > player.pos().x() + width)
            if(monstre->pos().y() <= player.pos().y() + (height / 2) && monstre->pos().y() >= player.pos().y() - (height /2)){
                monstre->takeDamages(this->getDmg());
            }
    }
}
