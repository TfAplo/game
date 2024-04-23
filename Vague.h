#ifndef VAGUE_H
#define VAGUE_H

#include <QVector>
#include <QTimer>
#include <QGraphicsScene>
#include "Monstre.h"
#include "Player.h"


class Vague : public QObject
{
    Q_OBJECT
public:
    explicit Vague(const vector<string> monstres, QGraphicsScene *scene, QTimer *gameTimer,Player *player=0);
    void genererNouveauTableauMonstre();



private slots:
    void apparaitreMonstre();

private:
    vector<Monstre*> tableauMonstres;
    vector<string> tableauMonstre;
    int currentIndex;
    QTimer *timer;
    QGraphicsScene *scene;
    QTimer *gameTimer;
    Player *player;
    int elapsedTime;

};

#endif // VAGUE_H
