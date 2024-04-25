#ifndef UPGRADEATTAQUESELFHEAL_H
#define UPGRADEATTAQUESELFHEAL_H

#include "upgradeAttaque.h"

class upgradeAttaqueSelfHeal : public upgradeAttaque
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static double cooldown;
    static double animationDuration;
    static double valueBoost;

public:
    upgradeAttaqueSelfHeal(Player* player,QTimer* gameTimer);

    virtual void effect();
    void affichage();

};

#endif // UPGRADEATTAQUESELFHEAL_H
