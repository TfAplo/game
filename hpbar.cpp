#include "hpbar.h"

HPBar::HPBar(qreal width, qreal height, QGraphicsItem *parent) :
    QObject(), QGraphicsRectItem(-1, -1, width+2, height+2, parent) {
    actualHP = new QGraphicsRectItem(0, 0, width, height, this);
    setBrush(QBrush(Qt::black));
    actualHP->setBrush(QBrush(Qt::red));

}

void HPBar::updateBar(qreal hp, qreal maxhp)
{
    qreal ratio = hp / maxhp;
    QRectF barRect = actualHP->rect();
    barRect.setWidth(barRect.width() * ratio);
    actualHP->setRect(barRect);
}
