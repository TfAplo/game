#include "Vague.h"
#include <QTimer>
#include "Ghost.h"
#include "Game.h"
#include "Sorcier.h"
#include "Cyclope.h"
#include "Boss.h"
#include <algorithm>
#include <random>


#include <iostream>

using namespace std;

Vague::Vague(const vector<string> monstres,QGraphicsScene *scene, QTimer *gameTimer,Player *player)
    : tableauMonstre(monstres), currentIndex(0),scene(scene),gameTimer(gameTimer),player(player) {
    connect(gameTimer, &QTimer::timeout, this, &Vague::apparaitreMonstre);
    elapsedTime=0;
    elapsedGameTimer=0;
    timeSpawn=2000;

}


void Vague::genererNouveauTableauMonstre() {
    random_device rd;
    mt19937 g(rd());
    shuffle(tableauMonstre.begin(), tableauMonstre.end(), g);
}


void Vague::apparaitreMonstre() {


    elapsedTime += 20;
    elapsedGameTimer+=20;

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

    if (elapsedGameTimer>=timeSpawn){
        elapsedGameTimer=0;
        if (currentIndex >= tableauMonstre.size()) {
            // Si tous les monstres ont été créés, apparaître le boss

            pair<double,double> positionM1 = Game::getRandomPos(*player, first_circle, second_circle);
            Monstre* nouveauMonstre = new Boss(positionM1, Boss_hp,Boss_speed,Boss_dmg, gameTimer, player, scene);
            scene->addItem(nouveauMonstre);
            Monstre::vectMonstre.push_back(nouveauMonstre);

            genererNouveauTableauMonstre();
            currentIndex=0;

            //amélioration des stats des monstres à chaque vague
            Ghost_hp+=0.2*Ghost_hp;
            Ghost_speed+=0.1*Ghost_speed;
            Ghost_dmg+=0.1*Ghost_dmg;

            Sorcier_hp+=0.2*Sorcier_hp;
            Sorcier_speed+=0.1*Sorcier_speed;
            Sorcier_dmg+=0.1*Sorcier_dmg;

            Cyclope_hp+=0.2*Cyclope_hp;
            Cyclope_speed+=0.1*Cyclope_speed;
            Cyclope_dmg+=0.1*Cyclope_dmg;

            Boss_hp+=0.2*Boss_hp;
            Boss_speed+=0.1*Boss_speed;
            Boss_dmg+=0.1*Boss_dmg;

            // à chaque nouvelle vague, les monstres apparaissent de plus en plus vite
            if (timeSpawn>=300){
                timeSpawn=0.80*timeSpawn;
            }else{
                timeSpawn=300;
            }


        }
        // Vérifie si currentIndex est inférieur à la taille du tableauMonstres
        else {
            // Génère des coordonnées aléatoires pour la position du monstre
            pair<double,double> positionM1 = Game::getRandomPos(*player,first_circle,second_circle);
            Monstre* nouveauMonstre= nullptr;
            // Crée un nouvel objet Monstre avec les données du monstre actuel dans le tableauMonstres
            if (tableauMonstre[currentIndex] == "ghost") {
                nouveauMonstre =new Ghost(positionM1,Ghost_hp,Ghost_speed,Ghost_dmg,gameTimer,player,scene);
            }
            else if (tableauMonstre[currentIndex] == "sorcier"){
                nouveauMonstre =new Sorcier(positionM1,Sorcier_hp,Sorcier_speed,Sorcier_dmg,gameTimer,player,scene);
            }
            else if (tableauMonstre[currentIndex] == "cyclope"){
                nouveauMonstre =new Cyclope(positionM1,Cyclope_hp,Cyclope_speed,Cyclope_dmg,gameTimer,player,scene);
            }

            scene->addItem(nouveauMonstre);// Ajoute le monstre à la scène
            Monstre::vectMonstre.push_back(nouveauMonstre);

        }
    }
}
