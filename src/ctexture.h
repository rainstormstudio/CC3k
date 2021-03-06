#ifndef CTEXTURE_H
#define CTEXTURE_H

#ifdef __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#elif __WIN32__
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#endif
#include <string>
#include <iostream>

class CTexture {
    SDL_Texture* texture;
    SDL_Texture* background;
    unsigned int numSrcRows;
    unsigned int numSrcCols;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    SDL_Color foreColor;
    SDL_Color backColor;
public:
    CTexture(SDL_Texture* texture, unsigned int numSrcRows, unsigned int numSrcCols, 
             unsigned int tileWidth, unsigned int tileHeight,
             unsigned int width, unsigned int height);
    ~CTexture();

    void setIndex(char index);
    void setDestPosition(int x, int y);
    void setSrcPosition(int x, int y);

    void setForeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    void setBackColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    void setBlendMode(SDL_BlendMode blending);
    void render(SDL_Renderer* renderer);
};

#endif
