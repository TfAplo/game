#ifndef CHUNK_H
#define CHUNK_H

#include <QVector>
#include <QPoint>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Chunk : public QObject {
    Q_OBJECT
public:
    Chunk(QPoint& position, QPoint& positionFictive, int size,QObject* parent = nullptr);

    void generateTerrain();
    void loadTerrain();
    void afficherChunk(QGraphicsScene* scene);
    void supprimerChunk(QGraphicsScene *scene);

    QPoint position;
    QPoint positionFictive;

private:
    int size;
    QGraphicsPixmapItem* pixmapItem;

};


#endif // CHUNK_H
