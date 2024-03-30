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
public:
    static vector<ChoixNiveauUp*> vecChoix;
    static vector<QGraphicsTextItem*> vecTitres;
    static vector<QPushButton*> vecBoutons;

    ChoixNiveauUp(Upgrade *upgrade, double x, double y, double largeur, double hauteur, QGraphicsScene *scene, QGraphicsView *view, QTimer *gameTimer, QGraphicsItem *parent = nullptr) :
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

signals:
    void signalFinChoix();

private slots:
    void handleButtonClick() {
        // Gérer le clic sur le bouton
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
        emit signalFinChoix();
        cout << "signal emis" << endl;
        //choix 1 : Epee lvl2
        //choix 1 : Shuriken lvl1
        //choix 3 : Chaussure lvl1
        //si clique ou bouton entrée sur choix 1 : appeler upgrade(epee)
        //si clique ou bouton entrée sur choix 2 : appeler creerObjet(shuriken)
        //si clique ou bouton entrée sur choix 3 : appeler creerObjet(Chaussure)
    }
};


#endif // CHOIXNIVEAUUP_H
