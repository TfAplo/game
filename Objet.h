#ifndef OBJET_H
#define OBJET_H

#include <string>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

using namespace std;

class Objet :public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    string nom;

public:
    Objet(string nom) :
        nom(nom) {}

};

#endif // OBJET_H
