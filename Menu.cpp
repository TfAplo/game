#include "Menu.h"
#include <QGraphicsProxyWidget>

Menu::Menu(QObject *parent) : QGraphicsScene(parent) {
    int windowWidth = 1280;
    int windowHeight = 720;
    // Création du fond d'écran
    QPixmap backgroundImage(":/graphics/backgrounds/background1.jpg");
    backgroundImage = backgroundImage.scaled(windowWidth-2, windowHeight, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *background = addPixmap(backgroundImage);
    background->setPos(0, 0);

    // Création des boutons
    buttonPlay = new QPushButton("Play");
    buttonSettings = new QPushButton("Settings");
    buttonExit = new QPushButton("Exit");

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
    connect(buttonPlay, &QPushButton::clicked, this, &Menu::displayCharacterSelection);
    connect(buttonExit, &QPushButton::clicked, this, &Menu::onExitClicked);

    // Ajout des boutons à la scène
    addWidget(buttonPlay);
    addWidget(buttonSettings);
    addWidget(buttonExit);

}

void Menu::displayCharacter(QString image, QString name, QString hp, QString dmg, QString speed, int posX, int posY)
{
    // Créer un rectangle noir avec des bordures blanches
    QGraphicsRectItem *characterRect = new QGraphicsRectItem(0, 0, 200, 300);
    characterRect->setPos(posX,posY);
    characterRect->setPen(QPen(Qt::white));
    characterRect->setBrush(QBrush(Qt::black));

    // Ajouter le rectangle à la scène
    addItem(characterRect);

    //ajouter le rectangle au vecteur pour l'effacer plus tard
    choixPersos.push_back(characterRect);

    // Ajouter du texte à l'intérieur du rectangle et du bouton
    QGraphicsPixmapItem *im = new QGraphicsPixmapItem(image, characterRect);
    QGraphicsTextItem *nameText = new QGraphicsTextItem(name, characterRect);
    QPushButton *buttonChoose = new QPushButton("Choose");
    ChooseButtons.push_back(buttonChoose);

    //connexion du bouton au signal pour choisir
    connect(buttonChoose, &QPushButton::clicked, this, &Menu::onPlaySignal);

    // Style et position du texte
    nameText->setPos(10, 10);
    nameText->setDefaultTextColor(Qt::white);
    nameText->setFont(QFont("Arial", 20, QFont::Bold));

    // Redimensionner l'image et centrer
    im->setPixmap(im->pixmap().scaled(96, 96, Qt::KeepAspectRatio));
    im->setPos((characterRect->boundingRect().width() - im->boundingRect().width()) / 2, 10);

    // Centrer le texte "name" en dessous de l'image
    nameText->setPos((characterRect->boundingRect().width() - nameText->boundingRect().width()) / 2, 10 + im->boundingRect().height() + 10);

    // Positionner le reste du texte
    int textXOffset = 10; // Décalage horizontal pour le texte
    int textYOffset = 30 + im->boundingRect().height() + 10 + nameText->boundingRect().height(); // Décalage vertical initial pour le texte
    int lineHeight = 20; // Hauteur de ligne

    // Créer et positionner le texte pour chaque attribut
    QGraphicsTextItem *hpLabelText = new QGraphicsTextItem("Health-Point: " + hp, characterRect);
    hpLabelText->setPos(textXOffset, textYOffset);
    hpLabelText->setDefaultTextColor(Qt::white);

    QGraphicsTextItem *dmgLabelText = new QGraphicsTextItem("Damage: " + dmg, characterRect);
    dmgLabelText->setPos(textXOffset, textYOffset + lineHeight);
    dmgLabelText->setDefaultTextColor(Qt::white);

    QGraphicsTextItem *speedLabelText = new QGraphicsTextItem("Speed: " + speed, characterRect);
    speedLabelText->setPos(textXOffset, textYOffset + 2 * lineHeight);
    speedLabelText->setDefaultTextColor(Qt::white);

    buttonChoose->setGeometry(posX+50,posY+260, 100,20);
    addWidget(buttonChoose);

}

void Menu::displayMenu()
{
    //suppression des éléments de la selection de persos
    foreach (QGraphicsRectItem* rect, choixPersos) {
        removeItem(rect);
    }
    choixPersos.clear();

    foreach (QPushButton* b, ChooseButtons) {
        delete b;
    }
    ChooseButtons.clear();
    delete buttonBackFromChoice;

    buttonPlay->show();
    buttonSettings->show();
    buttonExit->show();
}

void Menu::displayCharacterSelection()
{
    buttonPlay->hide();
    buttonSettings->hide();
    buttonExit->hide();

    buttonBackFromChoice = new QPushButton("<-");
    QString buttonStyleSheet =
        "QPushButton {"
        "   background-color: rgba(0, 0, 0, 40);"
        "   border: none;"
        "   font-size: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 100);"
        "}";

    buttonBackFromChoice->setStyleSheet(buttonStyleSheet);
    buttonBackFromChoice->setGeometry(50,50,70,70);
    connect(buttonBackFromChoice, &QPushButton::clicked, this, &Menu::displayMenu);

    QGraphicsTextItem *labelChoose = new QGraphicsTextItem("Choose your character");
    labelChoose->setDefaultTextColor(Qt::white);
    labelChoose->setFont(QFont("Arial", 20, QFont::Bold));
    labelChoose->setPos(640 - labelChoose->boundingRect().width()/2, 10);

    addItem(labelChoose);
    addWidget(buttonBackFromChoice);

    displayCharacter(":/graphics/Tiles/tile_0084.png", "Wizard","100", "10", "3.4", 100, 200);
    displayCharacter(":/graphics/Tiles/tile_0084.png", "Wizard","100", "10", "3.4", 100 +1280/3, 200);
    displayCharacter(":/graphics/Tiles/tile_0084.png", "Wizard","100", "10", "3.4", 100+ (1280/3)*2, 200);

}

void Menu::onExitClicked()
{
    emit onExitSignal();
}
