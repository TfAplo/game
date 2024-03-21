#ifndef MONSTRE_H
#define MONSTRE_H

#include "Personnage.h"

class Monstre : public Personnage {
    Q_OBJECT
public:
    Monstre(string  image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg,QGraphicsItem *parent = 0) :
        Personnage(image,position,current_hp,max_hp,speed,dmg,parent) {}

    virtual ~Monstre(){};

signals:

public slots:
};


#endif // MONSTRE_H
