#include "Vague.h"
#include <QTimer>
#include "Ghost.h"
#include "Game.h"
#include "Sorcier.h"
#include "Cyclope.h"
#include "Boss.h"

#include <iostream>

using namespace std;

Vague::Vague(const vector<string> monstres,QGraphicsScene *scene, QTimer *gameTimer,Player *player)
    : tableauMonstre(monstres), currentIndex(0),scene(scene),gameTimer(gameTimer),player(player) {
    // Créer un timer pour gérer l'apparition des monstres
    QTimer *timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Vague::apparaitreMonstre);
    timer->start(2000);
    elapsedTime=0;
}



void Vague::apparaitreMonstre() {


    elapsedTime += 5000; // Incrémente le temps écoulé de 1000 millisecondes (1 seconde)

    int rand_min = 0;
    int rand_max = 1600;


    double first_circle = 200;
    double second_circle = 800;

    srand(time(0));

    // Vérifie si le temps écoulé est supérieur ou égal à 30000 millisecondes (30 secondes)
    // et s'il reste des monstres à faire apparaître dans le tableauMonstres
    if (elapsedTime >= 30000 && currentIndex < tableauMonstre.size()) {
        currentIndex += 1; // Passe au prochain monstre dans le tableau
        elapsedTime = 0; // Réinitialise le temps écoulé à 0
    }

    // Vérifie si currentIndex est inférieur à la taille du tableauMonstres
    if (currentIndex < tableauMonstre.size()) {
        // Génère des coordonnées aléatoires pour la position du monstre
        pair<double,double> positionM1 = Game::getRandomPos(*player,first_circle,second_circle);
        Monstre* nouveauMonstre= nullptr;
        // Crée un nouvel objet Monstre avec les données du monstre actuel dans le tableauMonstres
        if (tableauMonstre[currentIndex] == "ghost") {
            nouveauMonstre =new Ghost(false,positionM1,gameTimer,player,scene);
        }
        else if (tableauMonstre[currentIndex] == "sorcier"){
            nouveauMonstre =new Sorcier(false,positionM1,gameTimer,player,scene);
        }
        else if (tableauMonstre[currentIndex] == "cyclope"){
            nouveauMonstre =new Cyclope(false,positionM1,gameTimer,player,scene);
        }

        scene->addItem(nouveauMonstre);// Ajoute le monstre à la scène
        Monstre::vectMonstre.push_back(nouveauMonstre);

    }else{
        // si tous les monstres ont été crées alors on fait apparaitre un boss
        if (currentIndex == tableauMonstre.size()){
            pair<double,double> positionM1 = Game::getRandomPos(*player,first_circle,second_circle);
            Monstre* nouveauMonstre= nullptr;
            nouveauMonstre =new Boss(false,positionM1,gameTimer,player,scene);
            scene->addItem(nouveauMonstre);// Ajoute le monstre à la scène
            Monstre::vectMonstre.push_back(nouveauMonstre);
        }


    }

}



