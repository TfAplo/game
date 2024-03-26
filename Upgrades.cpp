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
    int width = 100;
    int height = 50;
    int dmg = 10;
    // parcourir tous les monstres
    for(const auto& monstre : monstres){
        // vérifier si le monstre est dans la zone de dégâts
        if(monstre->pos().x() >= player.pos().x() && monstre->pos().x() <= player.pos().x() + width &&
            monstre->pos().y() >= player.pos().y() && monstre->pos().y() <= player.pos().y() + height){
            // le monstre est dans la zone de dégâts, lui infliger des dégâts
            monstre->takeDamage(dmg);
            cout << "Le monstre kill !" << endl;
        }
    }
}

