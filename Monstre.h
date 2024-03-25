#ifndef MONSTRE_H
#define MONSTRE_H

#include "Personnage.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QObject>


class Monstre : public Personnage {
    Q_OBJECT
private:
    QTimer *moveTimer;
    Player *m_player;
    QGraphicsScene * scene;
    bool degDistance;
public:
    Monstre(bool degDistance,const QString&  image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, Player *player=0,QGraphicsScene *scene=0,QGraphicsItem *parent = 0);
    Monstre(bool initNoCreation,bool degDistance,const QString&  image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg,Player *player=0,QGraphicsScene *scene=0,QGraphicsItem *parent = 0);
    virtual ~Monstre(){};
    void testMort();
    bool getDegDistance();
    void attackPlayer();

signals:

public slots:
    void move();
};


#endif // MONSTRE_H
