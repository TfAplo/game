#ifndef MAP_H
#define MAP_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <memory> // Pour std::unique_ptr
#include "Terrain.h"
using namespace std;

class Map {
public:
    Map() {}

    Map(const QString& pathNiveau) {
        genererMap(pathNiveau);
    }
    ~Map() = default;

    void ajouterTerrain(unique_ptr<Terrain> terrain);

    void genererMap(const QString& pathNiveau);

    void afficher(QGraphicsScene *scene);

private:
    vector<unique_ptr<Terrain>> terrains;
};

#endif // MAP_H
