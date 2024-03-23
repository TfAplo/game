#ifndef XPBAR_H
#define XPBAR_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsView>

class XPBar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    XPBar(qreal width, qreal height, QGraphicsItem *parent = nullptr);

    void updateBar(qreal xp, qreal limitxp, qreal niveau);
    void setWidth(qreal width, qreal xp, qreal limitxp, qreal niveau);
private:
    QGraphicsRectItem *actualXP;
    QGraphicsTextItem *label1;
    QGraphicsTextItem *label2;
};

#endif // XPBAR_H
