#include "Map.h"
#include <string>
#include <QDebug>
#include "Obstacle.h"
#include "Sol.h"
#include <memory>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <sstream>


using namespace std;

void Map::ajouterTerrain(unique_ptr<Terrain> terrain)
{
    terrains.push_back(std::move(terrain));
}

void Map::genererMap(const QString& pathNiveau)
{
    QFile file(pathNiveau);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur: Impossible d'ouvrir le fichier";
        return;
    }

    QTextStream in(&file);
    int i = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        stringstream ss(line.toStdString());
        vector<string> values;
        string value;

        // Lecture de chaque valeur séparée par une virgule
        while (getline(ss, value, ',')) {
            if (value.length() < 4) {
                value = string(4 - value.length(), '0') + value + ".png";
            }
            values.push_back(value);
        }

        // Traitement de chaque valeur de la ligne
        int j = 0;
        for (const auto& val : values) {
            QString tilePath = ":/graphics/Tiles/tile_" + QString::fromStdString(val);
            if (val == "0040") {
                unique_ptr<Obstacle> obstacle = make_unique<Obstacle>(tilePath, 16, 16, j * 16, i * 16);
                ajouterTerrain(std::move(obstacle));
            } else {
                unique_ptr<Sol> sol = make_unique<Sol>(tilePath, 16, 16, j * 16, i * 16);
                ajouterTerrain(std::move(sol));
            }
            j++;
        }
        i++;
    }
    file.close();
}

void Map::afficher(QGraphicsScene *scene)
{
    for (const auto& terrain: terrains){
        QPixmap pixmap(terrain->texture);
        QGraphicsPixmapItem* item = scene->addPixmap(pixmap);
        item->setPos(terrain->posX, terrain->posY);
    }
}
