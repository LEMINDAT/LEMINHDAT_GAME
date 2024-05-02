#ifndef SNAKE_H
#define SNAKE_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Prey.h"
#include "Map.h"

class Snake
{
    public:
        Snake();
        virtual ~Snake();

        void Init();
        void Start();
        bool LoadImages(SDL_Renderer* renderer);
        bool CollideWithBodyOrStone(Map MAP);
        bool CollideWith(BaseObject object);
        bool OverlapWith(BaseObject object);
        bool OverlapWith(Prey preys);
        void Update();
        void Draw(SDL_Renderer* renderer, Prey preys);
        void HandleEvent(SDL_Event event);
        deque<BaseObject> segment;
    protected:

    private:
        SDL_Texture* Head[12];
        SDL_Texture* Body[6];
        SDL_Texture* Tail[4];
};

#endif // SNAKE_H
