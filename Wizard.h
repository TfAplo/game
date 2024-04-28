#ifndef WIZARD_H
#define WIZARD_H
#include "Player.h"

class Wizard: public Player
{
    Q_OBJECT
private:
    static QString defaultImage;
    static pair<double, double> defaultPosition;
public:
    Wizard();
};

#endif // WIZARD_H
