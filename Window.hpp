#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#pragma once

using namespace std;

const u_int16_t WINDOW_WIDTH = 800;
const u_int16_t WINDOWS_HEIGHT = 600;

enum Movement 
{
    KeyUP , KeyDown, KeyLeft,KeyRight, KeyQuit,KeyRestart, KeyShoot
};

class Window
{

public:
    SDL_Renderer* renderer;
    SDL_Window* window;

    Window(const char* name);
    void Display();
    void background();
    TTF_Font* font = TTF_OpenFont("DejaVuSans.ttf", 40);
    ~Window();
};
