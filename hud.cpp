#include "hud.h"

HUD::HUD(Player *player, QTimer *gameTimer,QGraphicsScene *scene,QGraphicsView *view)
    : player(player), gameTimer(gameTimer), scene(scene), view(view)
{
    xpBar = player->getXPBar();
    scene->addItem(xpBar);

    //creation d'un affichage pour le timer
    QFont police;
    police.setBold(true);
    police.setPointSize(12);
    labelTimer = new QGraphicsTextItem("temps");
    labelTimer->setZValue(2);
    labelTimer->setFont(police);
    labelTimer->setDefaultTextColor(Qt::white);
    startTime = QTime::currentTime();
    scene->addItem(labelTimer);

}

void HUD::update()
{
    //update de l'HUD pour qu'il soit toujours present dans la fenetre
    QPointF topLeft = view->mapToScene(0, 0);
    QPointF topRight = view->mapToScene(view->viewport()->width(), 0);
    //update de la barre XP
    xpBar->setPos(topLeft.x(), topLeft.y());
    xpBar->setWidth(topRight.x() - topLeft.x(),player->getXP(), player->getlimitXP(),player->getNiveau());
    //update du temps et de sa position
    updateTime();
    float coordMilieuX = (topRight.x() + topLeft.x())/2 - labelTimer->boundingRect().width()/2;
    labelTimer->setPos(coordMilieuX, topLeft.y()+ 40);
    //update des icones des armes
    int i = 0;
    int j = 0;
    for(QGraphicsPixmapItem *item : pixItems){
        if(i == 0)
            j++;
        item->setPos(topLeft.x()+i*32, topLeft.y()+j*32);
        item->setZValue(2);
        i++;
        i %= 6;
    }

}

void HUD::updateTime()
{
    QTime currentTime = QTime::currentTime();
    int elapsed = startTime.secsTo(currentTime); // Calcule le temps écoulé en secondes
    int secondes = elapsed % 60;
    int minutes = elapsed / 60;
    //mise en forme du temps (0:01)
    QString formattedTime;
    formattedTime = QString::number(minutes) + ":" + QString("%1").arg(secondes, 2, 10, QChar('0'));

    labelTimer->setPlainText(formattedTime);
}

#include <iostream>
using namespace std;

void HUD::updateItems(vector<Upgrade*> &vec)
{
    for(QGraphicsPixmapItem *item : pixItems){
        scene->removeItem(item);
    }
    pixItems.clear();
    for(Upgrade *up : vec){
        QPixmap textureToAdd(up->getImageIcone());
        QPixmap pix(":/graphics/Tiles/tile_0060.png");
        QPainter painter(&pix);
        painter.drawPixmap(0, 0, textureToAdd);
        painter.end();
        QGraphicsPixmapItem* item = scene->addPixmap(pix);
        item->setZValue(2);
        item->setPixmap(pix.scaled(32, 32));
        pixItems.push_back(item);
    }

}

QString HUD::getTime()
{
    return labelTimer->toPlainText();
}

void HUD::hideTimer()
{
    labelTimer->hide();
}
