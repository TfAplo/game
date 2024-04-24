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

    // attributs concernant les stats des monstres
    double Ghost_hp=100.;
    double Ghost_speed=2.;
    double Ghost_dmg=10.;

    double Sorcier_hp=100.;
    double Sorcier_speed=1.;
    double Sorcier_dmg=10.;

    double Cyclope_hp=100;
    double Cyclope_speed=1.5;
    double Cyclope_dmg=10.;

    double Boss_hp=150.;
    double Boss_speed=1.;
    double Boss_dmg=20.;


};

#endif // VAGUE_H
