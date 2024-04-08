#ifndef ARME_H
#define ARME_H

#include "upgrade.h"

class Arme : public Upgrade {
    Q_OBJECT
private:


public:
    Arme(QString imageIcone, string nom, QGraphicsItem *parent = 0) :
        Upgrade(imageIcone, nom) {}

    bool estArme();
    bool estGadget();


signals:

public slots:

};

#endif // ARME_H
