#ifndef PLAYER_H
#define PLAYER_H

#include "Personnage.h"

class Player : public Personnage {
    Q_OBJECT
private:
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;
    double xp;

    //ajout
    double niveau = 0;
    double limiteXP;
    //fin ajout

public:
    Player(string image, pair<double, double> position, double current_hp, double max_hp, double speed,double dmg, double xp, double limiteXP,QGraphicsItem *parent = 0);

    virtual void details() override;
    virtual ~Player(){};
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    //ajout
    //recup xp
    //augmente xp
    //si besoin augmente niveau
    //si niveau augmenté, afficher les 3 choix
    //appeler methode de valentin (creerObjet(objet) ou upgrade(objet))
    void recupXP();
    void augmenterNiveau();


    void setXP(double);
    void ajouterXP(double);
    double getNiveau();
    void setNiveau(double);
    void augmenterNiveau(double);
    //fin ajout
signals:
    void signalToGame();
public slots:
    void move();
};

#endif // PLAYER_H
