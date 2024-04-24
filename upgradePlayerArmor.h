#ifndef UPGRADEPLAYERARMOR_H
#define UPGRADEPLAYERARMOR_H

#include "upgradePlayer.h"

class upgradePlayerArmor : public upgradePlayer
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static int valueBoost;
public:
    upgradePlayerArmor(Player* player);

    virtual void effect();
};

#endif // UPGRADEPLAYERARMOR_H
