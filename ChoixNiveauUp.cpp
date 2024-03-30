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
