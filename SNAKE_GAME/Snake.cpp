#include "Snake.h"

Snake::Snake()
{
    //ctor

    for(int i = 0; i < 12; i++){
        Head[i] = NULL;
    }
    for(int i = 0; i < 8; i++){
        Body[i] = NULL;
    }
    for(int i = 0; i < 4; i++){
        Tail[i] = NULL;
    }
}

Snake::~Snake()
{
    //dtor
}

void Snake::Init(Map MAP){

    BaseObject initHead, initTail;

    do{
       initHead.RandomGenerate();
    }while(MAP.StoneCollision(initHead));

    initHead.setTYPE(NORMAL);
    initTail = initHead;
    initTail.Move(CELL_SIZE*dx[initHead.getDIR()], CELL_SIZE*dy[initHead.getDIR()]);

    segment.push_back(initHead);
    segment.push_back(initTail);
}

bool Snake::LoadImages(SDL_Renderer* renderer){
    //Head
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 3; j++){
            string src = "Image/Head";
            src += cDIR[i];
            src += char(j+'0');
            src += ".png";
            Head[i*3+j-1] = loadTexture(renderer,  src);
//            cerr<<Src<<'\n';
            if(Head[i*3+j-1] == NULL){
                cerr<<src<<'\n';
                return false;
            }
        }
    }

    //Body
    Body[0] = loadTexture(renderer, "Image/BodyU.png");
    if(Body[0] == NULL){
        cerr<<"Image/BodyU.png";
        return false;
    }

    Body[1] = loadTexture(renderer, "Image/BodyL.png");
    if(Body[1] == NULL){
        cerr<<"Image/BodyL.png";
        return false;
    }

    for(int i = 0; i < 2; i++){
        for(int j = 2; j < 4; j++){
            string src = "Image/Body";
            src += cDIR[i];
            src += cDIR[j];
            src += ".png";
            Body[i*2+j] = loadTexture(renderer, src);
            if(Body[i*2+j] == NULL){
                return false;
            }
        }
    }

    //Tail
    for(int i=0; i<4; i++){
        string src = "Image/Tail";
        src += cDIR[i];
        src += ".png";
        Tail[i] = loadTexture(renderer, src);
        if(Tail[i] == NULL){
            cerr<<src<<'\n';
            return false;
        }
    }

    return true;
}

bool Snake::CollideWithBodyOrStone(Map MAP)
{
    if(MAP.StoneCollision(segment.front())){
        return true;
    }

    for (int i = 1; i < segment.size(); ++i) {
        if (segment.front().SamePosition(segment[i])) {
            return true;
        }
    }
    return false;
}

bool Snake::CollideWith(BaseObject object)
{
    int DIR1 = min(object.getDIR(), segment[1].getDIR()),
        DIR2 = max(object.getDIR(), segment[1].getDIR());
    return segment.front().SamePosition(object) ||
    (object.SamePosition(segment[1]) && ((DIR1 == UP && DIR2 == DOWN) ||
                              (DIR1 == LEFT && DIR2 == RIGHT)));
}

bool Snake::OverlapWith(BaseObject object){
    for(BaseObject cur: segment){
        if(cur.SamePosition(object)) return true;
    }
    return false;
}

bool Snake::OverlapWith(Prey preys){
    for(BaseObject object: preys.object){
        if(OverlapWith(object)) return true;
    }
    return false;
}

void Snake::Update(){
    BaseObject newHead = segment.front();
    newHead.Move(CELL_SIZE ,CELL_SIZE);

    segment.push_front(newHead);
}

void Snake::Popback(){
    segment.pop_back();
}

void Snake::Draw(SDL_Renderer* renderer, Prey preys){

    for (int i = 1; i + 1 < segment.size(); i++) {

        int nxtDir = segment[i+1].getDIR();
        int curDir = segment[i].getDIR();

        int id;
        if(curDir == nxtDir){
            id = (curDir < 2 ? 0 : 1);
        }
        else{
            // noi giua huong hien tai va huong nguoc lai cua huong sau do
            int reverseNxtDir = nxtDir ^ 1;
            int UD_Dir = min(reverseNxtDir, curDir);
            int LR_Dir = max(reverseNxtDir, curDir);
            id = UD_Dir * 2 + LR_Dir;
        }

        applyImage(renderer, Body[id], segment[i].getX(), segment[i].getY(), CELL_SIZE, CELL_SIZE, 0, 0);
    }
    //draw tail
    applyImage(renderer, Tail[segment.back().getDIR()], segment.back().getX(), segment.back().getY(), CELL_SIZE, CELL_SIZE, 0, 0);

    //draw head
    int id = segment.front().getDIR()*3;

    int manhattanDis = SCREEN_HEIGHT + SCREEN_WIDTH;
    for(int i = 0; i < preys.MaxPrey; i++){
        if(preys.object[i].getTYPE() != NORMAL){
            manhattanDis = min(manhattanDis, segment.front().ManhattanDist(preys.object[i]));
        }
    }
    manhattanDis /= CELL_SIZE;
    if(manhattanDis == 0 || manhattanDis == 2) id++;
    if(manhattanDis == 1) id += 2;

    int cWIDTH = (id < 6 ? 6 : 16);
    int cHEIGHT = (id < 6 ? 16 : 6);
    applyImage(renderer, Head[id], segment.front().getX() - cWIDTH/2, segment.front().getY() - cHEIGHT/2, CELL_SIZE + cWIDTH, CELL_SIZE + cHEIGHT, 0, 0);
}

void Snake::HandleEvent(SDL_Event event){
    int DIR = segment.front().getDIR();
    int newDIR = DIR;
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_UP: newDIR = UP;
            break;

            case SDLK_DOWN: newDIR = DOWN;
            break;

            case SDLK_LEFT: newDIR = LEFT;
            break;

            case SDLK_RIGHT: newDIR = RIGHT;
            break;

        }
    }

    if(newDIR + DIR == UP + DOWN || newDIR + DIR == LEFT + RIGHT){
        newDIR = DIR;
    }

    segment.front().setDIR(newDIR);
}
