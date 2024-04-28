#include "Wizard.h"

QString Wizard::defaultImage = QString(":/graphics/Tiles/tile_0084.png");
pair<double, double> Wizard::defaultPosition = make_pair(1200, 1200);

Wizard::Wizard(): Player(defaultImage, defaultPosition, 100.0, 100.0, 2.5, 10, 0, 100) {}

