#ifndef UPGRADE_H
#define UPGRADE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Upgrade: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QString imageIcone;
public:
    Upgrade(QString imageIcone,QGraphicsItem *parent = 0);
    QString getImageIcone() const;
};

#endif // UPGRADE_H
