#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <vector>

class Menu : public QGraphicsScene {
    Q_OBJECT
public:
    Menu(QObject *parent = nullptr);
    void displayCharacter(QString image,QString name,QString hp, QString dmg, QString speed, int posX, int posY);

private:
    //Menu
    QPushButton *buttonPlay;
    QPushButton *buttonSettings;
    QPushButton *buttonExit;

    //choix perso
    QPushButton *buttonBackFromChoice;
    std::vector<QGraphicsRectItem*> choixPersos;
    std::vector<QPushButton*> ChooseButtons;

public slots:
    void onExitClicked();
    void displayCharacterSelection();
    void displayMenu();

signals:
    void onPlaySignal();
    void onExitSignal();
};


#endif // MENU_H
