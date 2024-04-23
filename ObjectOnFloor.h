#ifndef OBJECTONFLOOR_H
#define OBJECTONFLOOR_H
#include <QPoint>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class objectOnFloor : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
protected:
    QGraphicsScene* scene;
private:
    QPointF position;
    QString imageIcone;


public:
    objectOnFloor(QPointF position, QString imageIcone,QGraphicsScene* scene,QGraphicsItem *parent = 0);

    virtual void catchObject() = 0;
    virtual ~objectOnFloor(){}
};

#endif // OBJECTONFLOOR_H
