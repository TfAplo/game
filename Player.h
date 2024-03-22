#ifndef PLAYER_H
#define PLAYER_H
#include "hpbar.h"

#include "Personnage.h"

class Player : public Personnage {
    Q_OBJECT
private:
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;
    double xp;
    HPBar *hpBar;

public:
    Player(string image, pair<double, double> position, double current_hp, double max_hp, double speed,double dmg, double xp,QGraphicsItem *parent = 0);

    virtual void details() override;
    virtual ~Player(){};
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void updateHPBar();
    void takeDamage(double dmg) override;
signals:

public slots:
    void move();
};

#endif // PLAYER_H
