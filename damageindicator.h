#ifndef DAMAGEINDICATOR_H
#define DAMAGEINDICATOR_H
#include <QGraphicsTextItem>
#include <QTimer>
#include <QGraphicsScene>

class DamageIndicator : public QGraphicsTextItem {
    Q_OBJECT
private:
    double dmg;
    int elapsedTime;
    int totalTime;
    QTimer *scaleTimer;
    QTimer *opacityTimer;
public:
    DamageIndicator(double posX, double posY,double dmg,QGraphicsItem *parent = nullptr);

private slots:
    void removeFromScene();
    void updateScale();
    void updateOpacity();
};

#endif // DAMAGEINDICATOR_H
