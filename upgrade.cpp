#include "upgrade.h"
//ajout
#include <string.h>
#include <vector>
#include "Arme.h"
#include "Gadget.h"
#include <iostream>
//fin ajout

using namespace std;

Upgrade::Upgrade(QString imageIcone, string nom, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), imageIcone(imageIcone), nom(nom)
{

}

//ajout
string Upgrade::getNom() {
    return nom;
}

int Upgrade::getNiveau() {
    return niveau;
}

void Upgrade::setNiveau(int niveau) {
    this->niveau = niveau;
}

vector<Upgrade*> Upgrade::initUpgrade(vector<pair<string, string>> vecUpgradesString) {
    vector<Upgrade*> vecUpgrades;
    for (auto it = vecUpgradesString.begin(); it != vecUpgradesString.end(); it++) {
        Upgrade *upgrade;
        if (it->first == "Arme") {
            upgrade = new Arme("images/arme.png", it->second);
        } else if (it->first == "Gadget") {
            upgrade = new Gadget("images/gadget.png", it->second);
        }
        vecUpgrades.push_back(upgrade);
    }
    for (Upgrade* upgrade : vecUpgrades) {
        cout << upgrade->getNom() << endl;
    }
    return vecUpgrades;
}
//fin ajout

QString Upgrade::getImageIcone() const
{
    return imageIcone;
}
