#include "CommonFunction.h"
#include "BaseObject.h"
#include "Snake.h"


BaseObject generateFood(Snake snake) {
    BaseObject food;

    do{
        food.RandomGenerate();
    }while(snake.CollideWithObject(food));

    return food;
}

void update(Snake& snake, BaseObject& food, bool& GameOver) {

    if (snake.CollideWithObject(food)) {
        food = generateFood(snake);
    }

    snake.NextStep();

    if (!snake.CollideWithObject(food)) {
        snake.Popback();
    }

    if (snake.CollideWithBody()) {
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

    SDL_Texture* foodTexture = loadTexture(renderer, "Image/Food.png");
    if(foodTexture == NULL){
        return 1;
    }

    Snake snake;

    snake.Init();

    if(!snake.LoadImages(renderer)){
        return 1;
    }

    BaseObject food = generateFood(snake);
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

//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if(!GameOver){
            update(snake, food, GameOver);
        }

        applyImage(renderer, backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        snake.Draw(renderer, food);
        applyImage(renderer, foodTexture, food.getX()-5, food.getY()-5, CELL_SIZE+10, CELL_SIZE+10);

        if(GameOver){
            applyImage(renderer, gameOverTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }
    CleanUp();
    SDL_Quit();

    return 0;
}
