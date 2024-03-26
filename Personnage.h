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
    QString image;
    pair<double, double> position;
    double current_hp;
    double max_hp;
    double dmg;


public:
    Personnage(const QString&  image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg,QGraphicsItem *parent = 0) :
        QObject(), QGraphicsPixmapItem(parent), image(image), position(position), current_hp(current_hp), max_hp(max_hp), speed(speed), dmg(dmg) {}

    void takeDamage(double dmg);

    void attack(Personnage& other);

    virtual void details();

    virtual ~Personnage(){};

    virtual void keyPressEvent(QKeyEvent *event);

    double speed;

    // crée par raph
    QPointF getPosition() const;
    pair<double,double> getPositionPair() const;
    double getCurrent_hp();
    void setPosition(const pair<double,double> newPosition);


    QString getImage() const;
    double getMax_hp() const;
    double getDmg() const;


signals:

public slots:
};

#endif // PERSONNAGE_H
