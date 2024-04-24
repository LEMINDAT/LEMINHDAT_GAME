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
        if(object[id].getTYPE() != NORMAL){
            if(MAP.Stone[object[id].getX()/CELL_SIZE][object[id].getY()/CELL_SIZE]){
                ok = false;
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
        if(object[i].getTYPE() != NORMAL){
            if(object[i].getTYPE() == RAT){
                object[i].Move(CELL_SIZE, CELL_SIZE);
                if(MAP.StoneCollision(object[i])){
                    if(object[i].getDIR() <= DOWN){
                        object[i].setDIR(UP + DOWN - object[i].getDIR());
                    }
                    else{
                        object[i].setDIR(LEFT + RIGHT - object[i].getDIR());
                    }
                    object[i].Move(CELL_SIZE, CELL_SIZE);
                }
            }
        }
        else{
            object[i].RandomGenerate();
        }
    }
}

void Prey::Draw(SDL_Renderer* renderer){
    for(int i =0; i<MaxPrey; i++){
        if(object[i].getTYPE() == RAT){
            int id = (object[i].getDIR() < 2 ? 0 : 2) + (object[i].getX() + object[i].getY())/CELL_SIZE%2;
            int flip = NONE;
            int cWIDTH = (id < 2 ? 10 : 30);
            int cHEIGHT = (id < 2 ? 30 : 10);

            if(object[i].getDIR() == DOWN){
                flip = VERTICAL;
            }

            if(object[i].getDIR() == RIGHT){
                flip = HORIZONTAL;
            }

            applyImage(renderer, Rat[id], object[i].getX() - cWIDTH/2, object[i].getY() - cHEIGHT/2,
                       CELL_SIZE + cWIDTH, CELL_SIZE + cHEIGHT, 0, flip);
        }
        else if(object[i].getTYPE() == FOOD){
            int cWIDTH = 10;
            int cHEIGHT = 10;
            applyImage(renderer, Food, object[i].getX() - cWIDTH/2, object[i].getY() - cHEIGHT/2,
                       CELL_SIZE + cWIDTH, CELL_SIZE + cHEIGHT, 0, NONE);
        }
    }
}
