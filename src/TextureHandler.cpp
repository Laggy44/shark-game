#include "TextureHandler.h"
#include "SDL.h"
#include "SDL_image.h"

TextureHandler* TextureHandler::theInstance = nullptr;

TextureHandler* TextureHandler::getTheInstance(){
    if (theInstance == nullptr){
        theInstance = new TextureHandler();
    }
    return theInstance;
}

bool TextureHandler::load(string filename, string ID, SDL_Renderer* renderer){

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr){
        cout << "Error: " << IMG_GetError() << endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr){
        cout << "Error: " << IMG_GetError() << endl;
        return false;
    }

    textureMap[ID] = texture;
    return true;

}

void TextureHandler::renderTexture(string ID, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip){

    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopyEx(renderer, textureMap[ID], &srcRect, &dstRect, 0, 0, flip);

}

void TextureHandler::renderFrame(string ID, int x, int y, int width, int height, int curRow, int curFrame, SDL_Renderer* renderer, double angle, int alpha, SDL_RendererFlip flip){

    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = width * curFrame;
    srcRect.y = height * curRow;
    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;

    SDL_SetTextureAlphaMod(textureMap[ID], alpha);
    SDL_RenderCopyEx(renderer, textureMap[ID], &srcRect, &dstRect, 0, 0, flip);

}

void TextureHandler::renderTile(string ID, int margin, int spacing, int x, int y, int width, int height, int curRow, int curFrame, SDL_Renderer* renderer){

    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = margin + (spacing + width) * curFrame;
    srcRect.y = margin + (spacing + height) * curRow;
    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopyEx(renderer, textureMap[ID], &srcRect, &dstRect, 0, 0, SDL_FLIP_NONE);

}












