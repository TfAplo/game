#include "Tank.h"

QString Tank::defaultImage = QString(":/graphics/Tiles/tile_0087.png");
pair<double, double> Tank::defaultPosition = make_pair(1200, 1200);

Tank::Tank(): Player(defaultImage, defaultPosition, 150.0, 150.0, 2.3, 8, 0, 100) {}

