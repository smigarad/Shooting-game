#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Window.hpp"
#include "Player.hpp"

#pragma once

class PlayerScore
{
    public:
    SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
    Position position;
    int score =3;


    PlayerScore(Position position, SDL_Renderer* renderer, TTF_Font* font);
    void Sub();
    void Draw();
    ~PlayerScore();
};