#include "Runner.h"

QString Runner::defaultImage = QString(":/graphics/Tiles/tile_0112.png");
pair<double, double> Runner::defaultPosition = make_pair(1200, 1200);

Runner::Runner(): Player(defaultImage, defaultPosition, 80.0, 80.0, 2.8, 8, 0, 100) {}

