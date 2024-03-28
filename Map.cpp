#include "Map.h"
using namespace std;

Map::Map(QGraphicsScene *scene): scene(scene){
    // Initialise tableau avec les bonnes dimensions
    tableau.resize(3); // 3 lignes
    for (int i = 0; i < 3; ++i) {
        tableau[i].resize(3); // 3 colonnes
    }
    genererMap();
    playerFact = QPoint(0,0);
}

void Map::genererMap()
{
    for (int i =0; i < 3; i++){
        for(int j =0; j<3;j++){
            QPoint qp(j*800,i*800);
            QPoint qpf(j*800-800,i*800-800);
            Chunk *c = new Chunk(qp,qpf, 800);
            tableau[i][j] = c;
            c->afficherChunk(scene);
        }
    }
}

QPoint Map::resoudrePosition(QPoint pos)
{
    QPoint qp(pos.x()/800,pos.y()/800);
    return qp;
}

/* Lorsque le player change de chunk des nouveaux sont générés et ceux hors de distance sont detruits*/
void Map::chunkUpdate(QPoint pos)
{
    //prend la position du player et la convertit en position fictive
    pos = QPoint(pos.x() - playerFact.x(), pos.y() - playerFact.y());
    QPoint playerPos = resoudrePosition(pos);

    //verifie si le joueur n'est plus dans le chunk du milieu
    if (playerPos.x() != 1 || playerPos.y() != 1){
        //recupere coord fict du chunk dans lequel on est
        QPoint coordFictNouveauMilieu = tableau[playerPos.y()][playerPos.x()]->positionFictive;

        //initialisation d'une nouvelle map pour remplacer l'ancienne
        vector<vector<Chunk*>> nouvelleMap;
        nouvelleMap.resize(3);
        for (int i = 0; i < 3; ++i) {
            nouvelleMap[i].resize(3);
        }

        //pour chaque chunk calcul de leur nouvelle position fictive
        for (int i =0; i < 3; i++){
            for(int j =0; j<3;j++){
                tableau[i][j]->positionFictive -= coordFictNouveauMilieu;
                QPoint p = tableau[i][j]->positionFictive;

                //vérifie si les nouvelles coordonnées du chunk sont hors du tableau
                if(p.x() < -800 || p.x() > 800 ||p.y() < -800 || p.y() > 800){
                    tableau[i][j]->supprimerChunk(scene);
                }else{
                    //si chunk encore dans le tableau on le met dans la nouvelle map
                    QPoint nouvellePos = resoudrePosition(QPoint(p.x()+800,p.y()+800));
                    nouvelleMap[nouvellePos.y()][nouvellePos.x()] = tableau[i][j];
                }
            }
        }

        // on parcourt la nouvelle map pour trouver les chunk manquantes et les créers
        for (int i =0; i < 3; i++){
            for(int j =0; j<3;j++){
                if (!nouvelleMap[i][j]){
                    QPoint position(tableau[i][j]->position.x() +coordFictNouveauMilieu.x(),tableau[i][j]->position.y() +coordFictNouveauMilieu.y());
                    QPoint positionFictive(j*800 -800, i*800-800);
                    nouvelleMap[i][j] = new Chunk(position,positionFictive,800);
                    nouvelleMap[i][j]->afficherChunk(scene);
                }
            }
        }

        //incrémentation de playerFact nous permet de calculer les coords fictives du personnage
        playerFact = QPoint(playerFact.x() + coordFictNouveauMilieu.x(), playerFact.y() + coordFictNouveauMilieu.y());
        //on remplace la map actuelle par la nouvelle
        tableau = nouvelleMap;
    }
}
