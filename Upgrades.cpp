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
    int dmg = 1000;
    int side = 1;
    /*
    if(touche == Qt::Key_Left){
        side = -1;
        cout << "left" << endl;
    }*/
    int width = 80 *side;
    int height = 130 *side;

    //cout << "test" << endl;
    // parcourir tous les monstres
    for(const auto& monstre : monstres){
        // vérifier si le monstre est dans la zone de dégâts
         if(monstre->pos().x()  >= player.pos().x() && monstre->pos().x()<= player.pos().x() + width &&
            monstre->pos().y() <= player.pos().y() + (height / 2) && monstre->pos().y() >= player.pos().y() - (height /2)){
               monstre->takeDamages(dmg);
        }
    }
}
