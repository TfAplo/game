#include "hud.h"

HUD::HUD(Player *player, QTimer *gameTimer,QGraphicsScene *scene,QGraphicsView *view)
    : player(player), gameTimer(gameTimer), scene(scene), view(view)
{
    xpBar = player->getXPBar();
    scene->addItem(xpBar);

}

void HUD::update()
{
    QPointF topLeft = view->mapToScene(0, 0);
    QPointF topRight = view->mapToScene(view->viewport()->width(), 0);
    xpBar->setPos(topLeft.x(), topLeft.y());
    xpBar->setWidth(topRight.x() - topLeft.x(),player->getXP(), player->getlimitXP(),player->getNiveau());
}
