#ifndef NIVEAU_H
#define NIVEAU_H


#include <vector>
#include <memory>
#include "Map.h"
#include "Monstre.h"
#include <QGraphicsScene>
#include "Player.h"
using namespace std;

class Niveau :public QGraphicsView{
public:
    Niveau();
    ~Niveau() = default;

    void ajouterEnnemi(unique_ptr<Monstre> monstre);

    void afficherNiveau();

    //void setMap(const Map& map_);

    QGraphicsScene * scene;
    QTimer *levelTimer;
    Player* player;

private:
    vector<unique_ptr<Monstre>> monstres;
    //Map map;
};

#endif // NIVEAU_H
