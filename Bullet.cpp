#include"Bullet.hpp"

Bullet::Bullet(Position pos, SDL_Renderer* renderer,const char* name)
:position(pos), renderer(renderer)
{
    rect.w = rect.h = BULLET_HEIGHT;
    rect.y = position.y;
    texture = IMG_LoadTexture(renderer, name);
}

void Bullet::Draw()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

void Bullet::Update(float dt)
{
    position.x -= velocity.x * 0.5 * dt;

    rect.x = position.x;
    rect.y = position.y;
    
}


Bullet::~Bullet()
{
    SDL_DestroyTexture(texture);
}