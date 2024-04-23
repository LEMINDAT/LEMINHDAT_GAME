#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 20;
const int STEP_SIZE = 1;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DIR_TOTAL
};

enum FlipState
{
    NONE,
    HORIZONTAL,
    VERTICAL,
    FLIP_TOTAL
};

enum ObjectType
{
    NORMAL,
    FOOD,
    RAT,
    TYPE_TOTAL
};

const char cDIR[4] = {'U', 'D', 'L', 'R'};
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Event event;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& imagePath);
void applyImage(SDL_Renderer* renderer, SDL_Texture* img, int Xpos, int Ypos, int WIDTH, int HEIGHT, double angle, int flip);
void CleanUp();

#endif // COMMONFUNCTION_H
