#include "Map.h"

Map::Map()
{
    //ctor
    freopen("Map/Map.txt", "r", stdin);
    for(int i = 0; i < SCREEN_HEIGHT/CELL_SIZE; i++){
        for(int j = 0; j < SCREEN_WIDTH/CELL_SIZE; j++){
            cin>>Stone[j][i];
//            cerr<<Stone[j][i]<<' ';
        }
//        cerr<<'\n';
    }
}

Map::~Map()
{
    //dtor
}

bool Map::LoadImages(SDL_Renderer* renderer)
{
    StoneTexture = loadTexture(renderer, "Image/Stone.png");
    if(StoneTexture == NULL){
        return false;
    }
    return true;
}

bool Map::StoneCollision(BaseObject object){
    if(Stone[object.getX()/CELL_SIZE][object.getY()/CELL_SIZE]){
        return true;
    }
    return false;
}

void Map::DrawStone(SDL_Renderer* renderer)
{
    for(int i = 0; i < SCREEN_HEIGHT/CELL_SIZE; i++){
        for(int j = 0; j < SCREEN_WIDTH/CELL_SIZE; j++){
            if(Stone[j][i]){
//                cerr<<j<<' '<<i<<'\n';
                applyImage(renderer, StoneTexture, j * CELL_SIZE, i * CELL_SIZE,
                           CELL_SIZE, CELL_SIZE, 0, NONE);
            }
        }
    }
}


