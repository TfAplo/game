#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <string>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

using namespace std;

class Personnage:public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    string image;
    pair<double, double> position;
    double current_hp;
    double max_hp;
    double dmg;

public:
    Personnage(string  image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, QGraphicsItem *parent) :
        QObject(), QGraphicsPixmapItem(parent), image(image), position(position), current_hp(current_hp), max_hp(max_hp), speed(speed), dmg(dmg) {}

    void takeDamage(double dmg);

    void attack(Personnage& other);

    virtual void details();

    virtual ~Personnage(){};

    virtual void keyPressEvent(QKeyEvent *event);

    //ajout
    pair<double, double> getPos();
    //fin ajout

    double speed;
signals:

public slots:
};

#endif // PERSONNAGE_H
