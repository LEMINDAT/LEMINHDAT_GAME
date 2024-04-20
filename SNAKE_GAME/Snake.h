#ifndef SNAKE_H
#define SNAKE_H

#include "CommonFunction.h"
#include "BaseObject.h"

class Snake
{
    public:
        Snake();
        virtual ~Snake();

        void Init();
        bool LoadImages(SDL_Renderer* renderer);
        bool CollideWithBody();
        bool CollideWithObject(BaseObject object);
        void NextStep();
        void Popback();
        void Draw(SDL_Renderer* renderer, BaseObject& food);
        void HandleEvent(SDL_Event event);
    protected:

    private:
        deque<BaseObject> segment;
        SDL_Texture* Head[12];
        SDL_Texture* Body[6];
        SDL_Texture* Tail[4];
};

#endif // SNAKE_H
