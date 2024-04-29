#ifndef CHUNK_H
#define CHUNK_H

#include <QVector>
#include <QPoint>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

using namespace std;

class Chunk : public QObject {
    Q_OBJECT
public:
    Chunk(QPoint& position, QPoint& positionFictive, int size,QObject* parent = nullptr);

    void generateTerrain();
    void loadTerrain();
    void afficherChunk(QGraphicsScene* scene);
    void supprimerChunk(QGraphicsScene *scene);
    int randomModifier();
    int randomNumber(int n);

    QPoint position;
    QPoint positionFictive;

private:
    int size;
    QGraphicsPixmapItem* pixmapItem;
};


#endif // CHUNK_H
