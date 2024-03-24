#include "Vague.h"
#include <QTimer>

using namespace std;

Vague::Vague(const QVector<Monstre*> monstres,QGraphicsScene *scene, QTimer *gameTimer,Player *player)
    : tableauMonstres(monstres), currentIndex(0),scene(scene),gameTimer(gameTimer),player(player) {
    // Créer un timer pour gérer l'apparition des monstres
    QTimer *timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Vague::apparaitreMonstre);
    timer->start(1000);
    elapsedTime=0;


}



void Vague::apparaitreMonstre() {

    elapsedTime += 1000; // Incrémente le temps écoulé de 1000 millisecondes (1 seconde)

    int rand_min = 0;
    int rand_max = 1600;

    // Vérifie si le temps écoulé est supérieur ou égal à 30000 millisecondes (30 secondes)
    // et s'il reste des monstres à faire apparaître dans le tableauMonstres
    if (elapsedTime >= 30000 && currentIndex < tableauMonstres.size()) {
        currentIndex += 1; // Passe au prochain monstre dans le tableau
        elapsedTime = 0; // Réinitialise le temps écoulé à 0
    }

    // Vérifie si currentIndex est inférieur à la taille du tableauMonstres
    if (currentIndex < tableauMonstres.size()) {
        // Génère des coordonnées aléatoires pour la position du monstre
        int coord11 = arc4random_uniform(rand_max - rand_min + 1) + rand_min;
        int coord21 = arc4random_uniform(rand_max - rand_min + 1) + rand_min;
        // Crée une paire de doubles représentant la position du monstre
        pair<double,double> positionM1 = make_pair(coord11, coord21);
        // Crée un nouvel objet Monstre avec les données du monstre actuel dans le tableauMonstres
        Monstre *monstre =new Monstre(tableauMonstres.at(currentIndex)->getImage(),positionM1,tableauMonstres.at(currentIndex)->getCurrent_hp(),tableauMonstres.at(currentIndex)->getMax_hp(),tableauMonstres.at(currentIndex)->speed,tableauMonstres.at(currentIndex)->getDmg(),player,scene);
        scene->addItem(monstre);// Ajoute le monstre à la scène

    }else{
        timer->stop();// Arrête le timer si tous les monstres ont été créés
    }

}



