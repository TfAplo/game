#include "chunk.h"

Chunk::Chunk(QPoint &position, QPoint &positionFictive, int size, QObject *parent)
    : position(position), positionFictive(positionFictive),size(size)
{

}

void Chunk::afficherChunk(QGraphicsScene *scene)
{
    QString path = QString(":/modules/map_80%1.png").arg(randomNumber(3));
    QPixmap pix(path);
    int rotationAngle = randomNumber(3) * 90;
    pix = pix.transformed(QTransform().rotate(rotationAngle));
    if (randomNumber(1) == 1)
        pix = pix.transformed(QTransform().scale(-1, 1));

    pixmapItem = scene->addPixmap(pix);

    pixmapItem->setPos(position);
    pixmapItem->setZValue(-1);
}

void Chunk::supprimerChunk(QGraphicsScene *scene)
{
    scene->removeItem(pixmapItem);
    delete pixmapItem;
}

int Chunk::randomNumber(int n)
{
    // Créer un générateur de nombres aléatoires
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, n);

    // Générer aléatoirement un nombre entre 0 et n
    return distrib(gen);
}

