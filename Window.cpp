#include "Window.hpp"

Window::Window(const char* name)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)) cout<<"Error with init SDL, Error: " << SDL_GetError()<< endl;
    if(TTF_Init()) cout<<"Error with font init" << SDL_GetError()<<endl;

    if(!(window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOWS_HEIGHT,SDL_WINDOW_SHOWN)))
    cout << "Error with creating window: "<<SDL_GetError()<<endl;
    if(!(renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC))) cout << "Error with creating renderer: "<<SDL_GetError()<<endl;
    
}

void Window::Display()
{
    
    SDL_RenderPresent(renderer);
}


void Window::background()
{
    SDL_SetRenderDrawColor(renderer,128,128,255,255);
    SDL_RenderClear(renderer);

               
}

Window::~Window()
{
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
}