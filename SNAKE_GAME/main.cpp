#include "CommonFunction.h"
#include "Map.h"
#include "BaseObject.h"
#include "Snake.h"

void update(Snake& snake, Prey& preys, SDL_Texture* BloodTexture, bool& GameOver, Map MAP) {

    snake.Update();
    preys.Update(MAP);

    bool Collision = false;
    for(int i = 0; i < preys.MaxPrey; i++){
        BaseObject& object = preys.object[i];
        if(object.getTYPE() == NORMAL){
            continue;
        }
        if(snake.CollideWith(object)){
            Collision = true;
            if(object.getTYPE() == RAT){
                int cWITDH = 60;
                int cHEIGHT = 60;
                applyImage(renderer, BloodTexture,
                           object.getX() - cWITDH/2, object.getY() - cHEIGHT/2,
                           CELL_SIZE + cWITDH, CELL_SIZE + cHEIGHT, 0, NONE);
            }
            do{
                preys.RandomGenerate(i, MAP);
            }while(snake.OverlapWith(object));
            break;
        }
    }

    if(!Collision){
        snake.Popback();
    }

    if(snake.CollideWithBodyOrStone(MAP)) {
        GameOver = true;
    }
}

bool Init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        SDL_Log("Window could not be created: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Renderer could not be created: %s\n", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Log("SDL_image could not initialize: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if(Init() == false){
        return 1;
    }

    //load images
    SDL_Texture* backgroundTexture = loadTexture(renderer, "Image/BackGround.jpg");
    if(backgroundTexture == NULL){
        return 1;
    }

    SDL_Texture* gameOverTexture = loadTexture(renderer, "Image/GameOver.png");
    if(gameOverTexture == NULL){
        return 1;
    }

    SDL_Texture* BloodTexture = loadTexture(renderer, "Image/Blood.png");
    if(BloodTexture == NULL){
        return 1;
    }

    Snake snake;
    Prey preys;
    Map MAP;

    snake.Init(MAP);
    preys.Init(MAP);

    if(!snake.LoadImages(renderer)){
        return 1;
    }
    if(!preys.LoadImages(renderer)){
        return 1;
    }
    if(!MAP.LoadImages(renderer)){
        return 1;
    }

    bool GameOver = false;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
            if(!GameOver){
                snake.HandleEvent(event);
            }
        }

        SDL_RenderClear(renderer);
        applyImage(renderer, backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

        if(!GameOver){
            update(snake, preys, BloodTexture, GameOver, MAP);
        }

        MAP.DrawStone(renderer);
        snake.Draw(renderer, preys);
        preys.Draw(renderer);

        if(GameOver){
            applyImage(renderer, gameOverTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    CleanUp();

    return 0;
}
