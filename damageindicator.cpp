#include "damageindicator.h"
#include <QGraphicsOpacityEffect>


DamageIndicator::DamageIndicator(double posX, double posY,double dmg,QGraphicsItem *parent)
    : QGraphicsTextItem(parent), dmg(dmg), elapsedTime(0), totalTime(1000) {
    setPos(posX+6, posY-15);
    setPlainText(QString::number(qRound(dmg)));
    QFont police;
    police.setBold(true); // Mettre en gras
    police.setPointSize(10);
    setFont(police);
    setDefaultTextColor(Qt::red);
    //apres une seconde la methode removeFromScene() sera appelée
    QTimer::singleShot(1000, this, &DamageIndicator::removeFromScene);

    scaleTimer = new QTimer(this);
    opacityTimer = new QTimer(this);

    connect(scaleTimer, &QTimer::timeout, this, &DamageIndicator::updateScale);
    connect(opacityTimer, &QTimer::timeout, this, &DamageIndicator::updateOpacity);

    scaleTimer->start(10);
    opacityTimer->start(10);
}

void DamageIndicator::removeFromScene()
{
    scene()->removeItem(this);
    delete this;
}

void DamageIndicator::updateScale()
{
    qreal scaleFactor = static_cast<qreal>(elapsedTime) / totalTime;
    setScale(1.0 + scaleFactor);
    elapsedTime += 10;
    if (elapsedTime > totalTime) {
        scaleTimer->stop();
    }
}

void DamageIndicator::updateOpacity()
{
    qreal opacityFactor = 1.0 - (static_cast<qreal>(elapsedTime) / totalTime);
    setOpacity(opacityFactor);
}
