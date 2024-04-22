#ifndef UPGRADEPLAYER_H
#define UPGRADEPLAYER_H
#include "upgrade.h"
#include "Player.h"

class upgradePlayer : public Upgrade
{
private:
    int boostValue;
    bool isUsed;
public:
    upgradePlayer(QString name,QString description,QString imageIcone,int boostValue,QGraphicsItem *parent = 0);

    //GETTER / SETTER
    int getBoostValue() const;
    void setBoostValue(int v);
    bool getIsUsed() const;
    void setIsUsed(bool b);

    // methodes
    virtual void defaultAttack(Player& player) = 0;
};

#endif // UPGRADEPLAYER_H
