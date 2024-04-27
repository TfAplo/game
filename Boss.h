#ifndef BOSS_H
#define BOSS_H

#include "Monstre.h"
#include <QGraphicsScene>
#include <QObject>

class Boss : public Monstre {
    Q_OBJECT
public:
    Boss(pair<double,double> position, double hp,double speed,double dmg,QTimer *gameTimer, Player *player = nullptr, QGraphicsScene *scene = nullptr, QGraphicsItem *parent = nullptr);

    virtual ~Boss(){};


    pair<double, double> getPosition() const;
    QTimer *getGameTimer() const;
    Player *getPlayer() const;
    QGraphicsScene *getScene() const;

private:
    pair<double,double> position;
    int elapsed;
    QTimer *gameTimer;
    Player *player;
    QGraphicsScene * scene;

public slots:
};
#endif // BOSS_H
