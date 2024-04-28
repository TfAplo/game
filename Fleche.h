#ifndef FLECHE_H
#define FLECHE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Monstre.h" // Assure-toi que Monstre est inclus et défini correctement

class Fleche : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Fleche(Player *player, Monstre *targetMonster, QGraphicsScene *scene, QTimer *gameTimer, double dmg, const QString &texturePath, QGraphicsItem *parent = nullptr);
    ~Fleche();

public slots:
    void move();

private:
    Player *player;
    Monstre *targetMonster;
    QGraphicsScene *scene;
    QTimer *gameTimer;
    double dmg;
};

#endif // FLECHE_H
