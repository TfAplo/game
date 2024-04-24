#ifndef UPGRADEATTAQUEHACHE_H
#define UPGRADEATTAQUEHACHE_H

#include "upgradeAttaque.h"

class upgradeAttaqueHache : public upgradeAttaque
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static double cooldown;
    static double animationDuration;

public:
    upgradeAttaqueHache(Player* player);

    virtual void effect();
    void affichage();

};

#endif // UPGRADEATTAQUEHACHE_H
