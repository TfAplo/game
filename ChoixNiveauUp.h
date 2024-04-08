#ifndef CHOIXNIVEAUUP_H
#define CHOIXNIVEAUUP_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QTimer>
#include <vector>
#include <iostream>
#include "upgrade.h"

using namespace std;

class ChoixNiveauUp : public QObject, public QGraphicsRectItem {
    Q_OBJECT
private:
    Upgrade *upgrade;
    QGraphicsTextItem *titre; // Titre du choix de niveau
    QPushButton *bouton; // Bouton de sélection
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *gameTimer;
    bool estNouveau;
public:
    static vector<ChoixNiveauUp*> vecChoix;
    static vector<QGraphicsPixmapItem*> vecImages;
    static vector<QPushButton*> vecBoutons;

    ChoixNiveauUp(Upgrade *upgrade, bool estNouveau, double x, double y, double largeur, double hauteur, QGraphicsScene *scene, QGraphicsView *view, QTimer *gameTimer, QGraphicsItem *parent = nullptr);

signals:
    void signalFinChoix(Upgrade *upgrade);

private slots:
    void handleButtonClick();
};


#endif // CHOIXNIVEAUUP_H
