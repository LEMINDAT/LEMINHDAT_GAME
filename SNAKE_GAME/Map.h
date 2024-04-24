#ifndef MAP_H
#define MAP_H

#include "CommonFunction.h"
#include "BaseObject.h"


class Map
{
    public:
        Map();
        virtual ~Map();

        bool Stone[SCREEN_WIDTH/CELL_SIZE][SCREEN_HEIGHT/CELL_SIZE];

        bool LoadImages(SDL_Renderer* renderer);
        bool StoneCollision(BaseObject object);
        void DrawStone(SDL_Renderer* renderer);
    protected:

    private:
        SDL_Texture* StoneTexture;
};

#endif // MAP_H
