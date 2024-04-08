#ifndef ORBEXP_H
#define ORBEXP_H

#include <string>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "Objet.h"

using namespace std;

class OrbeXP:public Objet {
    Q_OBJECT
private:
    pair<double, double> position;
    double valeurXP;
public:
    static vector<OrbeXP*> vecOrbeXP;

    OrbeXP(string nom, pair<double, double> position, double valeurXP) :
        Objet(nom), position(position), valeurXP(valeurXP) {
        vecOrbeXP.push_back(this);
    }

    pair<double, double> getPos();
    void setPos(pair<double, double>);
    double getXP();
    void setXP(double);
    static vector<OrbeXP*> getVecOrbeXP();
};

#endif // ORBEXP_H
