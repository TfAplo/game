#ifndef MAP_H
#define MAP_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "chunk.h"
using namespace std;

class Map {
public:
    Map(QGraphicsScene *scene);
    ~Map() = default;

    void genererMap();
    QPoint resoudrePosition(QPoint pos);
    void chunkUpdate(QPoint pos);


private:
    vector<vector<Chunk*>> tableau;
    QGraphicsScene *scene;
    QPoint playerFact;
};

#endif // MAP_H
