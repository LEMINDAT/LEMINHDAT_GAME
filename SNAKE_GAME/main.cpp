#include "CommonFunction.h"


struct Object {
    int x, y;

    bool operator == (const Object& other) {
        return max(abs(x - other.x), abs(y - other.y)) < CELL_SIZE;
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

    if (CollideWithFood(snake, food)) {
        food = generateFood(snake);
    }

    Object prv_back = snake.back();
    for (int i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    snake.front().y += CELL_SIZE * dy[DIR];
    snake.front().x += CELL_SIZE * dx[DIR];

    if(snake.front().x < 0) snake.front().x = SCREEN_WIDTH - CELL_SIZE;
    else if(snake.front().x == SCREEN_WIDTH) snake.front().x = 0;

    if(snake.front().y < 0) snake.front().y = SCREEN_HEIGHT - CELL_SIZE;
    else if(snake.front().y == SCREEN_HEIGHT) snake.front().y = 0;

    if (CollideWithFood(snake, food)) {
        snake.push_back(prv_back);
    }

    if (CollideWithBody(snake)) {
        GameOver = true;
    }
}

void drawSnake(SDL_Renderer* renderer, vector<Object> snake, SDL_Texture *Head[], int DIR, Object& food) {

    SDL_Rect rect;

    for (int i = snake.size() - 1; i > 0; i--) {

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

    int manhattanDis = (abs(snake.front().x - food.x) + abs(snake.front() .y - food.y)) / CELL_SIZE;
    int id = DIR*4;
    if(manhattanDis == 0 || manhattanDis == 2) id++;
    if(manhattanDis == 1) id+=2;
    applyImage(renderer, Head[id], snake.front().x-5, snake.front().y-5, CELL_SIZE+10, CELL_SIZE+10);
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

    SDL_Texture* Head[12];
    for(int i = 0; i < 4; i++){
        string fstSrc = "Image/Head";
        fstSrc += cDIR[i];
        for(int j = 1; j <= 3; j++){
            string Src = fstSrc + char(j+'0') + ".png";
            Head[i*4+j-1] = loadTexture(renderer,  Src);
            if(Head[i*4+j-1] == NULL){
                return 1;
            }
        }
    }

    int DIR = rand()%DIR_TOTAL;

    vector<Object> snake;
    //init snake
    Object initHead, initTail;
    initHead.RandomGenerate();
    initTail = {initHead.x+CELL_SIZE*dx[DIR], initHead.y+CELL_SIZE*dy[DIR]};

    snake.push_back(initHead);
    snake.push_back(initTail);

    Object food = generateFood(snake);
    bool GameOver = false;

    bool quit = false;
    bool isUpdated = true;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if(!GameOver){
                if(event.type == SDL_KEYDOWN){
                    isUpdated = true;
                    switch(event.key.keysym.sym){
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
                else if(event.type == SDL_KEYUP){
//                    isUpdated = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if(!GameOver && isUpdated){
            update(snake, food, DIR, GameOver);
        }

        applyImage(renderer, backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        drawSnake(renderer, snake, Head, DIR, food);
        applyImage(renderer, foodTexture, food.x-5, food.y-5, CELL_SIZE+10, CELL_SIZE+10);

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
