#include <iostream>
#include "Window.hpp"
#include "Player.hpp"
#pragma once

using namespace std;

const int BULLET_HEIGHT = 27;
const int BULLET_WEIGHT = 27;
const int MAX_BULLETS = 20;
class Bullet
{
public:
    Position position;
    Position velocity;
    SDL_Rect rect;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    Bullet(Position pos, SDL_Renderer* renderer, const char* name);
    void Draw();
    void Update(float dt);
    ~Bullet();
};
