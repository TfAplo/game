#ifndef UPGRADE_H
#define UPGRADE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Player.h"
//ajout
#include <string>
//fin ajout

using namespace std;

class Upgrade: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    Player* player;
private:
    QString name; // nom de l'upgrade
    QString description; // description de l'upgrade
    QString imageIcone; // chemin vers l'image utiliser pour l'icone
    int level = 1;

public:
    Upgrade(QString name,QString description,QString imageIcone, Player* player,QGraphicsItem *parent = 0);

    virtual void effect() = 0;
    virtual void setActif() = 0;

    QString getName() const;
    QString getDescription() const;
    QString getImageIcone() const;
    int getLevel() const;
    void levelUp();
};

#endif // UPGRADE_H
