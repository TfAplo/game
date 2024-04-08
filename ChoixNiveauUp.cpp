#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "Map.h"
#include "Player.h"
#include "ChoixNiveauUp.h"
#include <QTimer>
#include <cmath>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

using namespace std;

vector<ChoixNiveauUp*> ChoixNiveauUp::vecChoix;
vector<QGraphicsTextItem*> ChoixNiveauUp::vecTitres;
vector<QPushButton*> ChoixNiveauUp::vecBoutons;

ChoixNiveauUp::ChoixNiveauUp(Upgrade *upgrade, double x, double y, double largeur, double hauteur, QGraphicsScene *scene, QGraphicsView *view, QTimer *gameTimer, QGraphicsItem *parent) :
    QObject(), QGraphicsRectItem(x, y, largeur, hauteur, parent), upgrade(upgrade), scene(scene), view(view), gameTimer(gameTimer) {
    scene->addItem(this);
    setPos(x, y);
    setRect(0, 0, largeur, hauteur);

    // Ajouter un titre au choix
    QString nomUpgrade = QString::fromStdString(upgrade->getNom().append(" lvl ").append(to_string(upgrade->getNiveau())));
    titre = new QGraphicsTextItem(nomUpgrade, this);
    qreal textWidth = titre->boundingRect().width(); // Largeur du texte
    qreal textHeight = titre->boundingRect().height(); // Hauteur du texte
    titre->setPos((largeur/2-textWidth/2)-textWidth/6, 10); // Positionner le texte
    QFont font("Chiller", 20, QFont::Bold); // Police, taille, poids
    titre->setFont(font);
    titre->setDefaultTextColor(Qt::white); // Couleur du texte

    // Ajouter une image au choix

    // Ajouter un bouton au choix
    bouton = new QPushButton("Sélectionner", nullptr);
    scene->addWidget(bouton);
    QSize boutonSize = bouton->size();
    int buttonWidth = boutonSize.width();
    int buttonHeight = boutonSize.height();
    bouton->move(x + (largeur/2 - buttonWidth/2), y + (hauteur/1.1));

    // Remplir le rectangle avec une couleur marron
    QBrush brush(QColor(139, 69, 19)); // Couleur marron (RGB : 139, 69, 19)
    setBrush(brush);

    // Définir la couleur du contour du rectangle
    QPen pen(Qt::black); // Couleur noire pour le contour
    setPen(pen);

    setOpacity(0.9); // Opacité réglée à 90%


    // Connecter le signal clicked() du bouton à une fonction
    connect(bouton, &QPushButton::clicked, this, &ChoixNiveauUp::handleButtonClick);

    vecChoix.push_back(this);
    vecTitres.push_back(titre);
    vecBoutons.push_back(bouton);
}

void ChoixNiveauUp::handleButtonClick() {
    // Gérer le clic sur le bouton
    emit signalFinChoix(upgrade);

    for (ChoixNiveauUp *choix : vecChoix) {
        delete choix;
    }
    vecChoix.clear();

    vecTitres.clear();
    for (QPushButton *bouton : vecBoutons) {
        delete bouton;
    }
    vecBoutons.clear();

    gameTimer->start();
}
