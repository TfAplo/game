#ifndef RUNNER_H
#define RUNNER_H
#include "Player.h"

class Runner: public Player
{
    Q_OBJECT
private:
    static QString defaultImage;
    static pair<double, double> defaultPosition;
public:
    Runner();
};
#endif // RUNNER_H
