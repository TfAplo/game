#include "OrbeXP.h"
#include <iostream>
using namespace std;

OrbeXP::OrbeXP(string nom, pair<double, double> position, double valeurXP) : Objet(nom), position(position), valeurXP(valeurXP){


    QPixmap playerTexture(":/graphics/Tiles/tile_0114.png");
    setPixmap(playerTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur
    setPos(position.first, position.second);
    vecOrbeXP.push_back(this);


}

pair<double, double> OrbeXP::getPos() {
    return this->position;
}

void OrbeXP::setPosition(pair<double, double> position) {
    this->position = position;
}

double OrbeXP::getXP() {
    return this->valeurXP;
}

void OrbeXP::setXP(double valeurXP) {
    this->valeurXP = valeurXP;
}

vector<OrbeXP*> getVecOrbeXP() {
    return OrbeXP::vecOrbeXP;
}

vector<OrbeXP*> OrbeXP::vecOrbeXP;

