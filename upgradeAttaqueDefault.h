#ifndef UPGRADEATTAQUEDEFAULT_H
#define UPGRADEATTAQUEDEFAULT_H

#include "upgradeAttaque.h"

class upgradeAttaqueDefault : public upgradeAttaque
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static double cooldown;
    static double animationDuration;

public:
    upgradeAttaqueDefault(Player* player,QTimer* gameTimer);

    virtual void effect();
    void affichage();

};

#endif // UPGRADEATTAQUEDEFAULT_H
