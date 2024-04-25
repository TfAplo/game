#include "bombe.h"
#include "Monstre.h"

double bombe::rayonExplosion = 30;
QString bombe::imageIcone = QString(":/graphics/Tiles/bombe_pixel.png");

bombe::bombe(QGraphicsScene* scene, Player* player, int level):
    objectOnFloor(player->pos(),imageIcone,scene){
    this->level = level;

    explosionTimer = new QTimer(this);
    connect(explosionTimer, &QTimer::timeout, [=]() { explosion(player);  });
    explosionTimer->start(1000);
}

void bombe::catchObject(){
}

void bombe::explosion(Player* player){

    // recuperer la position du joueur
    QPointF Center = this->pos();

    int width = 80;
    int dmg = 50 + this->level * 5;

    //calculer une zone en cercle autour du joueur en fonction du level
    int taille = width + (300 * this->level) / 100;

    for(const auto& monstre : Monstre::vectMonstre){
        // si la position du monstre est dans le cercle on lui inflige des degats
        QPointF monsterPos = monstre->pos();

        double distance = sqrt(pow(monsterPos.x() - Center.x(), 2) + pow(monsterPos.y() - Center.y(), 2));

        if(distance <= taille){
            monstre->takeDamage(dmg);
        }

    }
    delete this;
}

