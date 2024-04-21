#include <iostream>
#include <cmath>
using namespace std;

#include "fonctions.h"

Fonctions::Fonctions() {}



// fonction de collision
bool Fonctions::isCollide(QPointF p1, QPointF p2){

    bool result = false;

    int tailleObj = 32;

    // calculer la distance entre les deux objets
    double axeX = p1.x() - p2.x();
    double axeY = p1.y() - p2.y();
    double distance = sqrt(pow(axeX,2) + pow(axeY,2));


    if(distance <= tailleObj){
        result = true;
    }
    return result;
}
