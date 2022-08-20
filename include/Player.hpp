#include <iostream>
#include "Window.hpp"

#pragma once

using namespace std;

struct Position
{
    float x;
    float y;
};

const uint8_t PLAYER_WIDTH = 80;
const uint8_t PLAYER_HEIGHT = 60;
const float PLAYER_SPEED =1;
const float ENEMY_SPEED = 0.4;

class Player
{


public:
    int health = 3;
    Position position ;
    Position velocity = {0,0};
    SDL_Rect rect;
    SDL_Renderer* renderer;
    SDL_Texture* spaceship;
    //SDL_Surface* sky = IMG_Load("sky.jpg");
    SDL_Texture* texture = IMG_LoadTexture(renderer, "resource/sky.jpg");
    SDL_Rect background_rect = {0,0,WINDOW_WIDTH,WINDOWS_HEIGHT};
    Player(Position position,SDL_Renderer* renderer,const char* name);
    void Draw();
    void Background();
    void Update(float dt);
    bool Collision(Position bullet);
    ~Player();
};

