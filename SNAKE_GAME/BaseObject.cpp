#include "BaseObject.h"

BaseObject::BaseObject()
{
    x = y = TYPE = DIR = 0;
}

BaseObject::~BaseObject()
{
    //dtor
}

bool BaseObject::SamePosition(const BaseObject& other) const
{
    return x == other.x && y == other.y;
}

bool BaseObject::operator == (const BaseObject& other) const
{
    return x == other.x && y == other.y && DIR == other.DIR && TYPE == other.TYPE;
}

void BaseObject::RandomGenerate()
{
    x = rand() % (SCREEN_WIDTH / CELL_SIZE) * CELL_SIZE;
    y = rand() % (SCREEN_HEIGHT / CELL_SIZE) * CELL_SIZE;
    DIR = rand() % DIR_TOTAL;
    TYPE = rand() % (TYPE_TOTAL*2) - TYPE_TOTAL;
    if(TYPE<0) TYPE = NORMAL;
}

BaseObject BaseObject::operator = (const BaseObject& other){
    x = other.x;
    y = other.y;
    DIR = other.DIR;
    TYPE = other.TYPE;
    return *this;
}

void BaseObject::Move(int Dx, int Dy){
    x += dx[DIR] * Dx;
    y += dy[DIR] * Dy;
}

void BaseObject::MoveThroughEdge(int Dx, int Dy){
    Move(Dx, Dy);

    if(x >= SCREEN_WIDTH) x -= SCREEN_WIDTH;
    if(y >= SCREEN_HEIGHT) y -= SCREEN_HEIGHT;

    if(x < 0) x += SCREEN_WIDTH;
    if(y < 0) y += SCREEN_HEIGHT;
}

int BaseObject::ManhattanDist(const BaseObject& other) const{
    return abs(x - other.x) + abs(y - other.y);
}

