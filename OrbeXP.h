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
    OrbeXP(string nom, pair<double, double> position);

    pair<double, double> getPos();
    void setPosition(pair<double, double>);
    double getXP();
    void setXP(double);

};

#endif // ORBEXP_H
