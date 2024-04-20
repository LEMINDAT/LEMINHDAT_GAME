#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "CommonFunction.h"

class BaseObject
{
    public:
        BaseObject();
        virtual ~BaseObject();

        bool operator == (const BaseObject& other) const;
        void RandomGenerate();
        BaseObject operator = (const BaseObject& other);
        int getX();
        int getY();
        int getDIR();
        void setX(int x_);
        void setY(int y_);
        void setDIR(int DIR_);
        void Move(int Dx, int Dy);

    protected:
        int x, y;
        int DIR;

    private:
};

#endif // BASEOBJECT_H
