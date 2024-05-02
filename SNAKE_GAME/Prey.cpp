#include "Prey.h"

Prey::Prey()
{
    //ctor
}

Prey::~Prey()
{
    //dtor
}

void Prey::Init(Map MAP){
    for(int i = 0; i < MaxPrey; i ++){
        RandomGenerate(i, MAP);
    }
}

void Prey::RandomGenerate(int id, Map MAP){
    bool ok = false;
    while(!ok){
        ok = true;
        object[id].RandomGenerate();
        if(object[id].TYPE != NORMAL){
            if(MAP.Stone[object[id].x/CELL_SIZE][object[id].y/CELL_SIZE]){
                ok = false;
                continue;
            }
            for(int i = 0; i < MaxPrey; i++){
                if( i != id && object[id] == object[i]){
                    ok = false;
                    break;
                }
            }
        }
    }
}

bool Prey::LoadImages(SDL_Renderer* renderer){
    Food = loadTexture(renderer, "Image/Food.png");
    if(Food == NULL){
        return false;
    }

    for(int i = 0; i <= 2; i+=2){
        for(int j = 0; j < 2; j++){
            string src = "Image/Rat";
            src += cDIR[i];
            src += char(j+'1');
            src += ".png";
            Rat[i+j] = loadTexture(renderer, src);
            if(Rat[i+j] == NULL){
                return false;
            }
        }
    }

    return true;
}

void Prey::Update(Map MAP){
    for(int i = 0; i < MaxPrey; i++ ){
        if(object[i].TYPE != NORMAL){
            if(object[i].TYPE == RAT){
                object[i].MoveThroughEdge(CELL_SIZE, CELL_SIZE);
                if(MAP.StoneCollision(object[i])){
                    if(object[i].DIR <= DOWN){
                        object[i].DIR = UP + DOWN - object[i].DIR;
                    }
                    else{
                        object[i].DIR = LEFT + RIGHT - object[i].DIR;
                    }
                    object[i].MoveThroughEdge(CELL_SIZE, CELL_SIZE);
                }
            }
        }
        else{
            RandomGenerate(i, MAP);
        }
    }
}

void Prey::Draw(SDL_Renderer* renderer){
    for(int i =0; i<MaxPrey; i++){
        if(object[i].TYPE == RAT){
            int id = (object[i].DIR < 2 ? 0 : 2) + (object[i].x + object[i].y)/CELL_SIZE%2;
            int flip = NONE;
            int cWIDTH = (id < 2 ? 10 : 30);
            int cHEIGHT = (id < 2 ? 30 : 10);

            if(object[i].DIR == DOWN){
                flip = VERTICAL;
            }

            if(object[i].DIR == RIGHT){
                flip = HORIZONTAL;
            }

            applyImage(renderer, Rat[id], object[i].x - cWIDTH/2, object[i].y - cHEIGHT/2,
                       CELL_SIZE + cWIDTH, CELL_SIZE + cHEIGHT, 0, flip);
        }
        else if(object[i].TYPE == FOOD){
            int cWIDTH = 10;
            int cHEIGHT = 10;
            applyImage(renderer, Food, object[i].x - cWIDTH/2, object[i].y - cHEIGHT/2,
                       CELL_SIZE + cWIDTH, CELL_SIZE + cHEIGHT, 0, NONE);
        }
    }
}
