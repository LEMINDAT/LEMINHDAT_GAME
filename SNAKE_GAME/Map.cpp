#include "Map.h"

Map::Map()
{
    //ctor
}

Map::~Map()
{
    //dtor
}

void Map::setMap(int id){
    imageSrc = "Map/Map";
    imageSrc += char(id + '0');
    imageSrc += ".txt";
}

void Map::LoadData(){
    ifstream in;
    in.open(imageSrc);
    for(int i = 0; i < SCREEN_HEIGHT/CELL_SIZE; i++){
        for(int j = 0; j < SCREEN_WIDTH/CELL_SIZE; j++){
            in>>Stone[j][i];
//            cerr<<Stone[j][i]<<' ';
        }
//        cerr<<'\n';
    }
    in.close();
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
    if(Stone[object.x/CELL_SIZE][object.y/CELL_SIZE]){
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


