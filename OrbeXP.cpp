#include "OrbeXP.h"
#include <iostream>
using namespace std;

pair<double, double> OrbeXP::getPos() {
    return this->position;
}

void OrbeXP::setPos(pair<double, double> position) {
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

