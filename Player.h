#ifndef PLAYER_H
#define PLAYER_H
#include "hpbar.h"
#include "xpbar.h"
#include <QGraphicsView>
#include "Personnage.h"
#include "upgrade.h"
#include <vector>

class Player : public Personnage {
    Q_OBJECT
private:
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;
    double xp;
    double niveau;
    double limiteXP;
    HPBar *hpBar;
    XPBar *xpBar;
    bool leftOriented;
    QPixmap playerTextureLeft;
    QPixmap playerTextureRight;
    vector<Upgrade*> upgrades;

public:
    Player(string image, pair<double, double> position, double current_hp, double max_hp, double speed,double dmg, double xp,QGraphicsItem *parent = 0);

    virtual void details() override;
    virtual ~Player(){};
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void updateHPBar();
    void takeDamage(double dmg) override;
    XPBar* getXPBar();
    void setXP(double);
    double getXP();
    double getlimitXP();
    double getNiveau();
    void ajouterXP(double);
    void updateOrientation(bool movesLeft);
    vector<Upgrade*> getUpgrades();

signals:

public slots:
    void move();
};

#endif // PLAYER_H
