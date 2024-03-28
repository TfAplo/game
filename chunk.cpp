#include "chunk.h"

Chunk::Chunk(QPoint &position, QPoint &positionFictive, int size, QObject *parent)
    : position(position), positionFictive(positionFictive),size(size)
{

}

void Chunk::afficherChunk(QGraphicsScene *scene)
{
    QPixmap pix(":/modules/map2_800.png");
    pixmapItem = scene->addPixmap(pix);
    pixmapItem->setPos(position);
    pixmapItem->setZValue(-1);
}

void Chunk::supprimerChunk(QGraphicsScene *scene)
{
    scene->removeItem(pixmapItem);
    delete pixmapItem;
}

