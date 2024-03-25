#include "Monstre.h"
#include "OrbeXP.h"
#include <QTimer>



using namespace std;

Monstre::Monstre(bool degDistance,const QString& image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg,Player *player,QGraphicsScene *scene,QGraphicsItem *parent) :
    Personnage(image,position,current_hp,max_hp,speed,dmg,parent), m_player(player),scene(scene), degDistance(degDistance)
{

    // Charger la texture du Monstre
    QPixmap playerTexture(image);
    setPixmap(playerTexture.scaled(32, 32)); // Ajuster la taille de la texture du joueur

    QPointF positionJoueur = player->getPosition();
    if (QPointF(position.first, position.second) == positionJoueur) {
        // Déplacer légèrement le monstre pour éviter la division par zéro
        position.first += 100.0; // Décalage horizontal arbitraire
        position.second += 100.0; // Décalage vertical arbitraire
        setPos(position.first, position.second);
    } else {
        // Positionner le monstre à sa position initiale
        setPos(position.first, position.second);
    }
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Monstre::move);
    moveTimer->start(15);

   QTimer::singleShot(10000, this, &Monstre::testMort);



}

Monstre::Monstre(bool initNoCreation,bool degDistance,const QString& image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg,Player *player,QGraphicsScene *scene,QGraphicsItem *parent) :
    Personnage(image,position,current_hp,max_hp,speed,dmg,parent), m_player(player),scene(scene),degDistance(degDistance)
{
}

void Monstre::move()
{
    // Obtenir les coordonnées actuelles du monstre
    qreal positionX = this->x();
    qreal positionY = this->y();

    // Récupérer la position actuelle du joueur
    qreal playerPositionX = m_player->x();
    qreal playerPositionY = m_player->y();

    // Calculer la direction vers le joueur
    qreal joueurX = playerPositionX;
    qreal joueurY = playerPositionY;
    qreal directionVersJoueurX = joueurX - positionX;
    qreal directionVersJoueurY = joueurY - positionY;

    // Normaliser la direction vers le joueur
    qreal length = qSqrt(directionVersJoueurX * directionVersJoueurX + directionVersJoueurY * directionVersJoueurY);
    if (length > 0.0) {
        directionVersJoueurX /= length;
        directionVersJoueurY /= length;
    }

    // Calculer le déplacement nécessaire pour se rapprocher de la cible
    qreal dx = directionVersJoueurX * speed;
    qreal dy = directionVersJoueurY * speed;

    // Définir une distance minimale entre le joueur et le monstre
    qreal distanceMinJM = 100.;
    qreal distanceMinMM=30.;

    // Calculer la distance entre le joueur et le monstre
    qreal distanceJoueurMonstre = qSqrt((positionX - playerPositionX) * (positionX - playerPositionX) + (positionY - playerPositionY) * (positionY - playerPositionY));


    // Vérifier les collisions avec les autres monstres
    for (QGraphicsItem *item : scene->items()) {
        if (Monstre *other_monster = dynamic_cast<Monstre*>(item)) {
            // Exclure le monstre lui-même
            if (other_monster != this) {
                // Calculer la distance entre les monstres
                qreal distanceMonstre = qSqrt((positionX - other_monster->x()) * (positionX - other_monster->x()) + (positionY - other_monster->y()) * (positionY - other_monster->y()));
                // Si la distance est inférieure à la distance minimale, ajuster le déplacement
                if (distanceMonstre < distanceMinMM) {
                    // Calculer la direction pour éviter la collision
                    qreal avoidDirectionX = positionX - other_monster->x();
                    qreal avoidDirectionY = positionY - other_monster->y();
                    // Normaliser la direction
                    qreal avoidLength = qSqrt(avoidDirectionX * avoidDirectionX + avoidDirectionY * avoidDirectionY);
                    if (avoidLength > 0.0) {
                        avoidDirectionX /= avoidLength;
                        avoidDirectionY /= avoidLength;
                    }
                    // Ajouter la direction d'évitement au déplacement
                    dx += avoidDirectionX * speed;
                    dy += avoidDirectionY * speed;
                }
            }
        }
    }

    if (degDistance){
        if (distanceJoueurMonstre<distanceMinJM){
            dx = 0; // Arrêter le déplacement en x
            dy = 0; // Arrêter le déplacement en y


        }
    }else{
        if (distanceJoueurMonstre<distanceMinMM){
            dx=0;
            dy=0;
            this->attack(*m_player);
        }
    }

    // Déplacer le monstre selon le déplacement calculé
    setPos(mapToParent(dx, dy));

}



void Monstre::testMort()
{
    // Marquer la direction dans laquelle le joueur souhaite se déplacer

    this->takeDamage(110.);
    if (getCurrent_hp() == 0){
        OrbeXP *orbe=new OrbeXP("nom",make_pair(x(),y()));

        scene->addItem(orbe);
        scene->removeItem(this);

        // Supprimer le monstre de la mémoire
        delete this;
    }

}

bool Monstre::getDegDistance(){
    return degDistance;
}



