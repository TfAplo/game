#include "xpbar.h"

XPBar::XPBar(qreal width, qreal height, QGraphicsItem *parent) :
    QObject(), QGraphicsRectItem(0, 0, width+2, height+2, parent) {
    actualXP = new QGraphicsRectItem(1, 1, width, height, this);
    setBrush(QBrush(Qt::black));
    actualXP->setBrush(QBrush(Qt::green));

    // Création des labels et deur police
    QFont police;
    police.setBold(true); // Mettre en gras
    police.setPointSize(12);
    label1 = new QGraphicsTextItem("0", actualXP);
    label1->setDefaultTextColor(Qt::white);
    label2 = new QGraphicsTextItem("1", actualXP);
    label2->setDefaultTextColor(Qt::white);
    label1->setFont(police);
    label2->setFont(police);
}

void XPBar::updateBar(qreal xp, qreal limitxp, qreal niveau)
{
    //calcul de la taille de la barre d'xp par rapport a limitxp
    qreal ratio = xp / limitxp;
    QRectF barRect = actualXP->rect();
    barRect.setWidth(barRect.width() * ratio);
    actualXP->setRect(barRect);
}

void XPBar::setWidth(qreal width, qreal xp, qreal limitxp, qreal niveau)
{
    //permet de reajuster la taille et la position de la barre d'xp quand le joueur est bougé ou que la fenetre est bougée
    QRectF newRect = rect();
    QRectF newRectxp = actualXP->rect();
    newRect.setWidth(width);
    newRectxp.setWidth(width-1);
    setRect(newRect);
    actualXP->setRect(newRectxp);
    updateBar(xp, limitxp,niveau);
    label1->setPos(5, 2);
    label1->setPlainText(QString::number(niveau));
    label2->setPos(newRectxp.width()-25, 2);
    label2->setPlainText(QString::number(niveau+1));
}
