#include "CommonFunction.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& imagePath) {

    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
    if (loadedSurface == NULL) {
        SDL_Log("Unable to load image: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == NULL) {
        SDL_Log("Unable to create texture from: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(loadedSurface);

    return texture;
}

void applyImage(SDL_Renderer* renderer, SDL_Texture* img, int Xpos, int Ypos, int WIDTH, int HEIGHT, double angle, int flip){
    SDL_Rect rect = {Xpos, Ypos, WIDTH, HEIGHT};
    SDL_RendererFlip flipState = (flip == NONE ? SDL_FLIP_NONE
                                  : (flip == HORIZONTAL ? SDL_FLIP_HORIZONTAL : SDL_FLIP_VERTICAL));
    SDL_RenderCopyEx(renderer, img, NULL, &rect, angle, NULL, flipState);
}

void CleanUp(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

