#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <string>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

using namespace std;

class Personnage:public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
protected:
    string image;
    pair<double, double> position;
    double current_hp;
    double max_hp;
    double dmg;

public:
    Personnage(string  image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg,QGraphicsItem *parent = 0);

    virtual void takeDamage(double dmg);

    void attack(Personnage& other);

    virtual void details();

    virtual ~Personnage(){};


    double speed;
signals:

public slots:
};

#endif // PERSONNAGE_H
