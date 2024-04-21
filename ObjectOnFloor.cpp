#include "objectOnFloor.h"

objectOnFloor::objectOnFloor(QPointF position, QString imageIcone, QGraphicsScene* scene,QGraphicsItem *parent) :
 QObject(), QGraphicsPixmapItem(parent)
{
    this->imageIcone = imageIcone;
    this->scene = scene;
    setPos(position);

    // poser l'objet sur la scene
    QGraphicsPixmapItem* objet = new QGraphicsPixmapItem(QPixmap(imageIcone));
    objet->setPos(position);
    objet->setScale(2);
    scene->addItem(objet);

}
