#include "objectOnFloor.h"

objectOnFloor::objectOnFloor(QPointF position, QString imageIcone, QGraphicsScene* scene,QGraphicsItem *parent) :
 QObject(), QGraphicsPixmapItem(QPixmap(imageIcone))
{
    this->imageIcone = imageIcone;
    this->scene = scene;
    setPos(position);

    // poser l'objet sur la scene
    this->setPos(position);
    this->setScale(2);
    scene->addItem(this);

}
