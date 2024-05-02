#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "CommonFunction.h"

class BaseObject
{
    public:
        int x, y;
        int DIR;
        int TYPE;

        BaseObject();
        virtual ~BaseObject();

        bool operator == (const BaseObject& other) const;
        bool SamePosition(const BaseObject& other) const;
        void RandomGenerate();
        BaseObject operator = (const BaseObject& other);
        void Move(int Dx, int Dy);
        void MoveThroughEdge(int Dx, int Dy);
        int ManhattanDist(const BaseObject& other) const;

    protected:

    private:
};

#endif // BASEOBJECT_H
