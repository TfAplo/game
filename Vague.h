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
    explicit Vague(const vector<Monstre*> monstres, QGraphicsScene *scene, QTimer *gameTimer,Player *player=0);




private slots:
    void apparaitreMonstre();

private:
    vector<Monstre*> tableauMonstres;
    int currentIndex;
    QTimer *timer;
    QGraphicsScene *scene;
    QTimer *gameTimer;
    Player *player;
    int elapsedTime;

};

#endif // VAGUE_H
