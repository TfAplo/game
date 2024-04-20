#ifndef HPBAR_H
#define HPBAR_H

#include <QGraphicsRectItem>
#include <QBrush>

class HPBar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    HPBar(qreal width, qreal height, QGraphicsItem *parent = nullptr);

    void updateBar(qreal hp, qreal maxhp);
private:
    QGraphicsRectItem *actualHP;
    qreal firstWidth;
};

#endif // HPBAR_H
