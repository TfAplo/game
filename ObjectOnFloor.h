#ifndef OBJECTONFLOOR_H
#define OBJECTONFLOOR_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "Player.h"

class ObjectOnFloor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QString image;
    pair<int, int> position;

public:
    ObjectOnFloor(QString image,pair<int, int> position,QGraphicsItem *parent = 0);

    // GETTER / SETTER
    QString getImage() const;
    pair<int,int> getPosition() const;
    void setPosition(pair<int,int> pos);

    virtual void catchObject(Player& player) = 0;
    virtual ~ObjectOnFloor(){}
};

#endif // OBJECTONFLOOR_H
