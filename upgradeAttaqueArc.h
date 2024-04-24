#ifndef UPGRADEATTAQUEARC_H
#define UPGRADEATTAQUEARC_H

#include "upgradeAttaque.h"

class upgradeAttaqueArc : public upgradeAttaque
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static double cooldown;
    static double animationDuration;

public:
    upgradeAttaqueArc(Player* player);

    virtual void effect();
    void affichage();

};

#endif // UPGRADEATTAQUEARC_H
