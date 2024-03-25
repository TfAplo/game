#include "upgrade.h"

Upgrade::Upgrade(QString imageIcone,QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), imageIcone(imageIcone)
{

}

QString Upgrade::getImageIcone() const
{
    return imageIcone;
}
