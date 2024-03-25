#include "Projectile.h"

using namespace std;

Projectile::Projectile(Player *player,QGraphicsScene * scene,pair<double, double> position) : player(player), scene(scene),positionM(position){


    QPixmap playerTexture(":/graphics/Tiles/tile_0102.png");
    setPixmap(playerTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur
    setPos(positionM.first, positionM.second);


}

Projectile::move(){

}
