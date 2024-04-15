#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>

class Menu : public QGraphicsScene {
    Q_OBJECT
public:
    Menu(QObject *parent = nullptr);

public slots:
    void onPlayClicked();
    void onExitClicked();

signals:
    void onPlaySignal();
    void onExitSignal();
};


#endif // MENU_H
