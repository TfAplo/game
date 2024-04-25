#ifndef UPGRADEATTAQUESHIELD_H
#define UPGRADEATTAQUESHIELD_H

#include "upgradeAttaque.h"

class upgradeAttaqueShield : public upgradeAttaque
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static double cooldown;
    static double animationDuration;

public:
    upgradeAttaqueShield(Player* player,QTimer* gameTimer);

    virtual void effect();
    void affichage();

};

#endif // UPGRADEATTAQUESHIELD_H
