#ifndef UPGRADEPLAYER_H
#define UPGRADEPLAYER_H
#include "upgrade.h"
#include <QTimer>

class upgradePlayer : public Upgrade
{
private:
    int valueBoost;

public:
    upgradePlayer(QString name, QString description,QString imageIcone, Player* player,int valueBoost,QGraphicsItem *parent = 0);

    virtual void effect() = 0;
    virtual void setActif();

    void setValueBoost(int b);
    int getValueBoost() const;
};

#endif // UPGRADEPLAYER_H
