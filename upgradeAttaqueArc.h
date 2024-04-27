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
    QTimer *gameTimer;

public:
    upgradeAttaqueArc(Player* player, QTimer *gameTimer);

    virtual void effect();
    void affichage();
    double calculDistance(const QPointF &point1, const QPointF &point2);
};

#endif // UPGRADEATTAQUEARC_H
