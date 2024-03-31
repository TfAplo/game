#ifndef CYCLOPE_H
#define CYCLOPE_H

#include "Monstre.h"
#include <QGraphicsScene>
#include <QObject>

class Cyclope : public Monstre {
    Q_OBJECT
public:
    Cyclope(bool initNoCreation, pair<double,double> position, QTimer *gameTimer, Player *player = nullptr, QGraphicsScene *scene = nullptr, QGraphicsItem *parent = nullptr);

    virtual ~Cyclope(){};


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
#endif // CYCLOPE_H
