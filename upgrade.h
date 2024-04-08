#ifndef UPGRADE_H
#define UPGRADE_H

#include <QGraphicsPixmapItem>
#include <QObject>
//ajout
#include <string>
//fin ajout

using namespace std;

class Upgrade: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    string nom;
    QString imageIcone;
    int niveau = 1;
public:
    Upgrade(QString imageIcone, string nom, QGraphicsItem *parent = 0);
    QString getImageIcone() const;
    //ajout
    string getNom();
    int getNiveau();
    void setNiveau(int niveau);
    void incrementerNiveau();
    static vector<Upgrade*> initUpgrade(vector<pair<string, string>> vecUpgradesString);
    virtual bool estArme() = 0;
    virtual bool estGadget() = 0;
    //fin ajout
};

#endif // UPGRADE_H
