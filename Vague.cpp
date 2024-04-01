#include "Vague.h"
#include "Game.h"
#include <QTimer>

#include <iostream>

using namespace std;

Vague::Vague(const vector<Monstre*> monstres,QGraphicsScene *scene, QTimer *gameTimer,Player *player)
    : tableauMonstres(monstres), currentIndex(0),scene(scene),gameTimer(gameTimer),player(player) {
    // Créer un timer pour gérer l'apparition des monstres
    QTimer *timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Vague::apparaitreMonstre);
    timer->start(200);
    elapsedTime=0;
}



void Vague::apparaitreMonstre() {


    elapsedTime += 1000; // Incrémente le temps écoulé de 1000 millisecondes (1 seconde)

    int rand_min = 0;
    int rand_max = 1600;


    double first_circle = 200;
    double second_circle = 800;

    srand(time(0));

    // Vérifie si le temps écoulé est supérieur ou égal à 30000 millisecondes (30 secondes)
    // et s'il reste des monstres à faire apparaître dans le tableauMonstres
    if (elapsedTime >= 30000 && currentIndex < tableauMonstres.size()) {
        currentIndex += 1; // Passe au prochain monstre dans le tableau
        elapsedTime = 0; // Réinitialise le temps écoulé à 0
    }
    // si on arrive à la fin du vecteur alors on fait apparaitre les monstres des deux dernières vagues
    if (currentIndex==tableauMonstres.size()){
        // Génère des coordonnées aléatoires pour la position du monstre

        pair<double,double> positionM1 = Game::getRandomPos(*player,first_circle,second_circle);


        // Crée un nouvel objet Monstre avec les données du monstre de l'index précédent dans le tableauMonstres
        Monstre *monstre1 =new Monstre(tableauMonstres.at(currentIndex-1)->getDegDistance(),tableauMonstres.at(currentIndex-1)->getImage(),positionM1,tableauMonstres.at(currentIndex-1)->getCurrent_hp(),tableauMonstres.at(currentIndex-1)->getMax_hp(),tableauMonstres.at(currentIndex-1)->speed,tableauMonstres.at(currentIndex-1)->getDmg(),gameTimer,player,scene);
        scene->addItem(monstre1);// Ajoute le monstre à la scène
        Monstre::vectMonstre.push_back(monstre1);


        // Génère des coordonnées aléatoires pour la position du monstre
        /*
        pair<double,double> positionM2 = Game::getRandomPos(*player,first_circle,second_circle);
        // Crée un nouvel objet Monstre avec les données du monstre de l'index précédent dans le tableauMonstres
        Monstre *monstre2 =new Monstre(tableauMonstres.at(currentIndex-2)->getDegDistance(),tableauMonstres.at(currentIndex-2)->getImage(),positionM2,tableauMonstres.at(currentIndex-2)->getCurrent_hp(),tableauMonstres.at(currentIndex-2)->getMax_hp(),tableauMonstres.at(currentIndex-2)->speed,tableauMonstres.at(currentIndex-2)->getDmg(),gameTimer,player,scene);
        scene->addItem(monstre2);// Ajoute le monstre à la scène
        Monstre::vectMonstre.push_back(monstre2);
*/

    }else{
        // Vérifie si currentIndex est inférieur à la taille du tableauMonstres
        if (currentIndex < tableauMonstres.size()) {
            // Génère des coordonnées aléatoires pour la position du monstre
            pair<double,double> positionM1 = Game::getRandomPos(*player,first_circle,second_circle);

            // Crée un nouvel objet Monstre avec les données du monstre actuel dans le tableauMonstres
            Monstre *monstre =new Monstre(tableauMonstres.at(currentIndex)->getDegDistance(),tableauMonstres.at(currentIndex)->getImage(),positionM1,tableauMonstres.at(currentIndex)->getCurrent_hp(),tableauMonstres.at(currentIndex)->getMax_hp(),tableauMonstres.at(currentIndex)->speed,tableauMonstres.at(currentIndex)->getDmg(),gameTimer,player,scene);
            scene->addItem(monstre);// Ajoute le monstre à la scène
            Monstre::vectMonstre.push_back(monstre);

        }else{
            timer->stop();// Arrête le timer si tous les monstres ont été créés
        }
    }

}
