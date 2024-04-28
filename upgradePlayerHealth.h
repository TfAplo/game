#ifndef UPGRADEPLAYERHEALTH_H
#define UPGRADEPLAYERHEALTH_H

#include "upgradePlayer.h"

class upgradePlayerHealth : public upgradePlayer
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static int valueBoost;
public:
    upgradePlayerHealth(Player* player);

    virtual void effect();
};

#endif // UPGRADEPLAYERHEALTH_H
