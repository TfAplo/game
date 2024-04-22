#include "upgrade.h"
//ajout
/*
#include <string>
#include <vector>
#include "Arme.h"
#include "Gadget.h"
#include <iostream>
//fin ajout
*/

using namespace std;

Upgrade::Upgrade(QString name,QString description,QString imageIcone,QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    this->name = name;
    this->description = description;
    this->imageIcone = imageIcone;
}

// increment le niveau de l'upgrade par 1
void Upgrade::levelUp(){
    this->level = this->getLevel() + 1;
}




// ---- GETTERS -----

QString Upgrade::getName() const {
    return this->name;
}
QString Upgrade::getDescription() const{
    return this->description;
}
QString Upgrade::getImageIcone() const{
    return this->imageIcone;
}
int Upgrade::getLevel() const{
    return  this->level;
}





//ajout
/*
string Upgrade::getN() {
    return nom;
}

int Upgrade::getNiveau() {
    return niveau;
}

void Upgrade::setNiveau(int niveau) {
    this->niveau = niveau;
}

void Upgrade::incrementerNiveau() {
    this->niveau++;
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
*/
