#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 20;

enum KeyPressSurfaces
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_TOTAL
};

struct Object {
    int x, y;

    bool operator == (const Object& o) {
        return x == o.x && y == o.y;
    }

    void RandomGenerate(){
        x = rand() % (SCREEN_WIDTH / CELL_SIZE) * CELL_SIZE;
        y = rand() % (SCREEN_HEIGHT / CELL_SIZE) * CELL_SIZE;
    }
};


bool CollideWithBody(vector<Object> snake) {
    for (int i = 1; i < snake.size(); ++i) {
        if (snake.front().x == snake[i].x && snake.front().y == snake[i].y) {
            return true;
        }
    }
    return false;
}

bool CollideWithFood(vector<Object> snake, Object food) {
    for(Object segment: snake){
        if(segment == food){
            return true;
        }
    }
    return false;
}

Object generateFood(vector<Object> snake) {
    Object food;

    do{
        food.RandomGenerate();
    }while(CollideWithFood(snake, food));

    return food;
}

void update(vector<Object>& snake, Object& food, int& DIR, bool& GameOver) {

    Object prv_back = snake.back();
    for (int i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    switch (DIR) {
        case DIR_UP:
            snake.front().y -= CELL_SIZE;
            break;
        case DIR_DOWN:
            snake.front().y += CELL_SIZE;
            break;
        case DIR_LEFT:
            snake.front().x -= CELL_SIZE;
            break;
        case DIR_RIGHT:
            snake.front().x += CELL_SIZE;
            break;
    }

    if(snake.front().x<0) snake.front().x = SCREEN_WIDTH - CELL_SIZE;
    else if(snake.front().x==SCREEN_WIDTH) snake.front().x = 0;

    if(snake.front().y<0) snake.front().y = SCREEN_HEIGHT - CELL_SIZE;
    else if(snake.front().y==SCREEN_HEIGHT) snake.front().y = 0;

    if (CollideWithFood(snake, food)) {
        snake.push_back(prv_back);
        food = generateFood(snake);
    }

    if (CollideWithBody(snake)) {
        GameOver = true;
    }
}

void drawSnake(SDL_Renderer *renderer, vector<Object> snake) {

    SDL_Rect rect;

    for (int i = snake.size() - 1; i >= 0; i--) {

        Object segment = snake[i];

        if(i%2==0){
            SDL_SetRenderDrawColor(renderer, 150, 100, 200, 0);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 100, 100, 150, 0);
        }

        rect = {segment.x, segment.y, CELL_SIZE, CELL_SIZE};

        if(i == 0){
            rect = {segment.x-5, segment.y-5, CELL_SIZE+10, CELL_SIZE+10};
        }

        SDL_RenderFillRect(renderer, &rect);
    }
}

void drawBackground(SDL_Renderer *renderer, SDL_Texture* backgroundTexture){
    SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &rect);
}

void drawGameOver(SDL_Renderer *renderer, SDL_Texture* gameOverTexture){
    SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &rect);
}

void drawFood(SDL_Renderer *renderer, SDL_Texture* foodTexture, Object food){
    SDL_Rect rect = {food.x-5, food.y-5, CELL_SIZE+10, CELL_SIZE+10};
    SDL_RenderCopy(renderer, foodTexture, NULL, &rect);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& imagePath) {

    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
    if (loadedSurface == NULL) {
        cerr << "Unable to load image " << imagePath << "! SDL_image Error: " << IMG_GetError() << '\n';
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == NULL) {
        cerr << "Unable to create texture from " << imagePath << "! SDL Error: " << SDL_GetError() << '\n';
        return NULL;
    }

    SDL_FreeSurface(loadedSurface);

    return texture;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
        return 1;
    }

    SDL_Texture* backgroundTexture = loadTexture(renderer, "BackGround.jpg");
    if (backgroundTexture == NULL) {
        return 1;
    }

    SDL_Texture* gameOverTexture = loadTexture(renderer, "GameOver.png");
    if (gameOverTexture == NULL) {
        return 1;
    }

    SDL_Texture* foodTexture = loadTexture(renderer, "Food.png");
    if (foodTexture == NULL) {
        return 1;
    }

    vector<Object> snake;
    snake.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

    Object food = generateFood(snake);
    int DIR = rand()%DIR_TOTAL;
    bool GameOver = false;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if(!GameOver && e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                    if(DIR != DIR_DOWN) DIR = DIR_UP;
                    break;

                    case SDLK_DOWN:
                    if(DIR != DIR_UP) DIR = DIR_DOWN;
                    break;

                    case SDLK_LEFT:
                    if(DIR != DIR_RIGHT) DIR = DIR_LEFT;
                    break;

                    case SDLK_RIGHT:
                    if(DIR != DIR_LEFT) DIR = DIR_RIGHT;
                    break;

                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if(!GameOver){
            update(snake, food, DIR, GameOver);
        }

        drawBackground(renderer, backgroundTexture);
        drawSnake(renderer, snake);
        drawFood(renderer, foodTexture, food);

        if(GameOver){
            drawGameOver(renderer, gameOverTexture);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
