#ifndef PREY_H
#define PREY_H

#include "CommonFunction.h"
#include "BaseObject.h"

class Prey
{
    public:
        const int MaxPrey = 3;
        BaseObject object[5];

        Prey();
        virtual ~Prey();

        void RandomGenerate(int id);
        bool LoadImages(SDL_Renderer* renderer);
        void Update();
        void Draw(SDL_Renderer* renderer);

    protected:

    private:
        SDL_Texture* Rat[4];
        SDL_Texture* Food;
};

#endif // PREY_H
