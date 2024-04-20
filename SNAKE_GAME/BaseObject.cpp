#include "BaseObject.h"

BaseObject::BaseObject()
{
    x = y = 0;
    DIR = 0;
}

BaseObject::~BaseObject()
{
    //dtor
}
bool BaseObject::operator == (const BaseObject& other) const
{
    return x == other.x && y == other.y;
}

void BaseObject::RandomGenerate()
{
    x = rand() % (SCREEN_WIDTH / CELL_SIZE) * CELL_SIZE;
    y = rand() % (SCREEN_HEIGHT / CELL_SIZE) * CELL_SIZE;
    DIR = rand() % DIR_TOTAL;
}

BaseObject BaseObject::operator = (const BaseObject& other){
    x = other.x;
    y = other.y;
    DIR = other.DIR;
}

int BaseObject::getX(){
    return x;
}

int BaseObject::getY(){
    return y;
}

int BaseObject::getDIR(){
    return DIR;
}

void BaseObject::setX(int x_){
    x = x_;
}

void BaseObject::setY(int y_){
    y = y_;
}

void BaseObject::setDIR(int DIR_){
    DIR = DIR_;
}

void BaseObject::Move(int Dx, int Dy){
    x += Dx;
    y += Dy;
}

