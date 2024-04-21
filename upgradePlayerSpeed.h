#ifndef UPGRADEPLAYERSPEED_H
#define UPGRADEPLAYERSPEED_H

#include "upgradePlayer.h"

class upgradePlayerSpeed : public upgradePlayer
{
private:
    static QString name;
    static QString description;
    static QString imageIcone;
    static int valueBoost;
public:
    upgradePlayerSpeed(Player* player);

    virtual void effect();
};

#endif // UPGRADEPLAYERSPEED_H
