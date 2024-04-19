#include "ObjectOnFloor.h"

ObjectOnFloor::ObjectOnFloor( QString image,pair<int, int> position,QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), image(image), position(position){
    this->position = position;
    this->image = image;
}

QString ObjectOnFloor::getImage() const{
    return this->image;
}
pair<int,int> ObjectOnFloor::getPosition() const{
    return this->position;
}
void ObjectOnFloor::setPosition(pair<int,int> pos){
    this->position = make_pair(pos.first, pos.second);
}

//void ObjectOnFloor::catchObject(){}
