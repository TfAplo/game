#include "Monstre.h"
#include "OrbeXP.h"
#include "Projectile.h"
#include <QTimer>
#include <vector>



using namespace std;

vector<Monstre*> Monstre::vectMonstre;

Monstre::Monstre(bool initNoCreation,bool degDistance,const QString& image, pair<double, double> position, double current_hp, double max_hp, double speed, double dmg, QTimer *gameTimer,Player *player,QGraphicsScene *scene,QGraphicsItem *parent) :
    Personnage(image,position,current_hp,max_hp,speed,dmg,parent), m_player(player),scene(scene), degDistance(degDistance),gameTimer(gameTimer)
{
    //QTimer::singleShot(10000,this,&Monstre::testMort);
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
    qreal directionVersJoueurX = playerPositionX - x();
    qreal directionVersJoueurY = playerPositionY - y();

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
    qreal distanceMinJM = 200.;
    qreal distanceMinMM=30.;

    // Calculer la distance entre le joueur et le monstre
    qreal distanceJoueurMonstre = qSqrt((positionX - playerPositionX) * (positionX - playerPositionX) + (positionY - playerPositionY) * (positionY - playerPositionY));

    // Vérifier les collisions avec les autres monstres
    for (Monstre* other_monster : vectMonstre) {
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


    if (degDistance){
        if (distanceJoueurMonstre<distanceMinJM){
            dx = 0; // Arrêter le déplacement en x
            dy = 0; // Arrêter le déplacement en y
            attackPlayer();

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

    // tester si le monstre est mort
    this->testMort();

}


void Monstre::attackPlayer(){
    if (elapsed>3000){
        elapsed=0;
        Projectile *p1 = new Projectile(m_player,scene,make_pair(x(),y()),gameTimer,make_pair(m_player->x(),m_player->y()),this->getDmg());
        scene->addItem(p1);

    }
    elapsed+=20;
}

void Monstre::testMort()
{
    //this->takeDamage(110.);
    if (getCurrent_hp() == 0){
        OrbeXP *orbe=new OrbeXP("nom",make_pair(x(),y()),10.);

        scene->addItem(orbe);

        scene->removeItem(this);
        vectMonstre.erase(remove(vectMonstre.begin(), vectMonstre.end(), this), vectMonstre.end());
        delete this;

    }

}

bool Monstre::getDegDistance(){
    return degDistance;
}




