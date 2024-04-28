#ifndef TANK_H
#define TANK_H

#include "Player.h"

class Tank: public Player
{
    Q_OBJECT
private:
    static QString defaultImage;
    static pair<double, double> defaultPosition;
public:
    Tank();
};

#endif // TANK_H
