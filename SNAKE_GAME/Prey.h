#ifndef PREY_H
#define PREY_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Map.h"

class Prey
{
    public:
        const int MaxPrey = 3;
        BaseObject object[5];

        Prey();
        virtual ~Prey();

        void Init(Map MAP);
        void RandomGenerate(int id, Map MAP);
        bool LoadImages(SDL_Renderer* renderer);
        void Update(Map MAP);
        void Draw(SDL_Renderer* renderer);

    protected:

    private:
        SDL_Texture* Rat[4];
        SDL_Texture* Food;
};

#endif // PREY_H
