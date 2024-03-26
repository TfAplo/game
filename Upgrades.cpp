#include "Upgrades.h"
#include <vector>
#include "Game.h"
#include <QString>
#include "Monstre.h"
#include <iostream>

using namespace std;

//constructeur
Upgrades::Upgrades(QString name, QString description, int level,double cooldown) {
    this->name = name;
    this->description = description;
    this->level = level;
    this->cooldown = cooldown;
}

// methode pour incrementer le niveau de l'upgrade
void Upgrades::upgradeLevel(Player& player)
{
    this->level += 1;
}


//met un coup dans un rayon de 5 cases devant lui sur une largeur de 3 cases
void Upgrades::defaultAttack(Player& player, vector<Monstre*> monstres){
    int width = 5;
    int height = 3;
    int dmg = 10;
    //calculer la zone dans laquelle les monstres prennent des degats en X
    for(const auto& monstre : monstres){
        if(monstre->pos().x() <= player.pos().x() + width || monstre->pos().x() > player.pos().x()){
            // en Y
            if(monstre->pos().y() <= player.pos().y() + height || monstre->pos().y() > player.pos().y()){
                // dans la zone pour subir des degats
                monstre->takeDamage(dmg);
                cout << "kill" << endl;
            }
        }
    }

}
