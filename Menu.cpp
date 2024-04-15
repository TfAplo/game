#include "Menu.h"

Menu::Menu(QObject *parent) : QGraphicsScene(parent) {
    int windowWidth = 1280;
    int windowHeight = 720;
    // Création du fond d'écran
    QPixmap backgroundImage(":/graphics/backgrounds/background1.jpg");
    backgroundImage = backgroundImage.scaled(1278, 720, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *background = addPixmap(backgroundImage);
    background->setPos(0, 0);

    // Création des boutons
    QPushButton *buttonPlay = new QPushButton("Play");
    QPushButton *buttonSettings = new QPushButton("Settings");
    QPushButton *buttonExit = new QPushButton("Exit");

    QString buttonStyleSheet =
        "QPushButton {"
        "   background-color: rgba(0, 0, 0, 40);"
        "   border: none;"
        "   padding: 10px 20px;"
        "   font-size: 30px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 100);"
        "}";

    buttonPlay->setStyleSheet(buttonStyleSheet);
    buttonSettings->setStyleSheet(buttonStyleSheet);
    buttonExit->setStyleSheet(buttonStyleSheet);

    // Positionnement des boutons
    int buttonWidth =0.3*windowWidth;
    int buttonHeight =0.1*windowHeight;
    int middleWidth = windowWidth/2 - buttonWidth/2;
    int yPos = (windowHeight - (3 * buttonHeight + 2 * 20)) / 2; // Calcul de la position verticale du premier bouton

    buttonPlay->setGeometry(middleWidth, yPos, buttonWidth, buttonHeight);
    yPos += buttonHeight + 20; // Incrément de la position pour le prochain bouton
    buttonSettings->setGeometry(middleWidth, yPos, buttonWidth, buttonHeight);
    yPos += buttonHeight + 20;
    buttonExit->setGeometry(middleWidth, yPos, buttonWidth, buttonHeight);

    //ajout des evenements sur chaque bouton
    connect(buttonPlay, &QPushButton::clicked, this, &Menu::onPlayClicked);
    connect(buttonExit, &QPushButton::clicked, this, &Menu::onExitClicked);

    // Ajout des boutons à la scène
    addWidget(buttonPlay);
    addWidget(buttonSettings);
    addWidget(buttonExit);
}

void Menu::onPlayClicked()
{
    emit onPlaySignal();
}

void Menu::onExitClicked()
{
    emit onExitSignal();
}
