#ifndef UPGRADEATTAQUEBOMBES_H
#define UPGRADEATTAQUEBOMBES_H
#include "Player.h"
#include "upgradeAttaque.h"

class upgradeAttaqueBombes : public upgradeAttaque
{

private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static double cooldown;
    static double animationDuration;

public:
    upgradeAttaqueBombes(Player* player);

    virtual void effect();
    void affichage();

};


#endif // UPGRADEATTAQUEBOMBES_H
