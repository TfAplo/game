#ifndef SORCIER_H
#define SORCIER_H

#include "Monstre.h"
#include <QGraphicsScene>
#include <QObject>

class Sorcier : public Monstre {
    Q_OBJECT
public:
    Sorcier(bool initNoCreation, pair<double,double> position, QTimer *gameTimer, Player *player = nullptr, QGraphicsScene *scene = nullptr, QGraphicsItem *parent = nullptr);

    virtual ~Sorcier(){};


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




#endif // SORCIER_H
