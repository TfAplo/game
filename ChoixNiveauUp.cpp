#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "ChoixNiveauUp.h"
#include <QTimer>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

using namespace std;

vector<ChoixNiveauUp*> ChoixNiveauUp::vecChoix;
vector<QGraphicsPixmapItem*> ChoixNiveauUp::vecImages;
vector<QPushButton*> ChoixNiveauUp::vecBoutons;

ChoixNiveauUp::ChoixNiveauUp(Upgrade *upgrade, bool estNouveau, double x, double y, double largeur, double hauteur, QGraphicsScene *scene, QGraphicsView *view, QTimer *gameTimer, QGraphicsItem *parent) :
    QObject(), QGraphicsRectItem(x, y, largeur, hauteur, parent), upgrade(upgrade), estNouveau(estNouveau), scene(scene), view(view), gameTimer(gameTimer) {
    scene->addItem(this);
    setPos(x, y);
    setRect(0, 0, largeur, hauteur);

    // Ajouter un titre au choix
    QString nomUpgrade;
    if (estNouveau) {
        nomUpgrade = QString::fromStdString(upgrade->getNom().append(" lvl ").append(to_string(upgrade->getNiveau())));
    } else {
        nomUpgrade = QString::fromStdString(upgrade->getNom().append(" lvl ").append(to_string(upgrade->getNiveau()+1)));
    }
    titre = new QGraphicsTextItem(nomUpgrade, this);
    qreal textWidth = titre->boundingRect().width(); // Largeur du texte
    qreal textHeight = titre->boundingRect().height(); // Hauteur du texte
    titre->setPos((largeur/2-textWidth/2)-textWidth/6, 10); // Positionner le texte
    QFont font("Chiller", 20, QFont::Bold); // Police, taille, poids
    titre->setFont(font);
    titre->setDefaultTextColor(Qt::white); // Couleur du texte

    // Ajouter une image au choix
    // Chargez l'image à l'aide de QPixmap
    QString image = ":/graphics/UpgradeImages/" + QString::fromStdString(upgrade->getNom()) + ".png";
    QPixmap pixmap(image);
    QPixmap newPixmap = pixmap.scaled(160, 160);

    // Créez un objet QGraphicsPixmapItem en utilisant l'image chargée
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(newPixmap);

    // Définissez la position de l'image
    pixmapItem->setPos(x + 5, y +80); // Remplacez x et y par les coordonnées où vous voulez placer l'image

    // Ajoutez l'objet QGraphicsPixmapItem à votre scène
    scene->addItem(pixmapItem);

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
    vecImages.push_back(pixmapItem);
    vecBoutons.push_back(bouton);
}

void ChoixNiveauUp::handleButtonClick() {
    // Gérer le clic sur le bouton
    emit signalFinChoix(upgrade);

    for (ChoixNiveauUp *choix : vecChoix) {
        delete choix;
    }
    vecChoix.clear();

    for (QGraphicsPixmapItem *image : vecImages) {
        delete image;
    }
    vecImages.clear();
    for (QPushButton *bouton : vecBoutons) {
        delete bouton;
    }
    vecBoutons.clear();

    gameTimer->start();
}
