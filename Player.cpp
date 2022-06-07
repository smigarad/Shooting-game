#include "Player.hpp"

Player::Player(Position position, SDL_Renderer* renderer,const char* name)
: position(position), renderer(renderer)
{
    rect.x = position.x;
    rect.y = position.y;
    rect.h  = PLAYER_HEIGHT;
    rect.w = PLAYER_WIDTH;
    spaceship = IMG_LoadTexture(renderer,name);
}
void Player::Draw()
{

    rect.x = position.x;
    rect.y = position.y;
    
    SDL_RenderCopy(renderer, spaceship, NULL, &rect);
    SDL_RenderDrawRect(renderer,&rect);
}

void Player::Update(float dt)
{
   
    position.y += velocity.y * 0.5 * dt;
    position.x += velocity.x * 0.5 * dt;

    if (position.y <0) position.y =0;
    else if(position.y > (WINDOWS_HEIGHT - PLAYER_HEIGHT))  position.y = WINDOWS_HEIGHT - PLAYER_HEIGHT;
   
    if(position.x <0) position.x=0;
    else if (position.x > (WINDOW_WIDTH - PLAYER_WIDTH)) position.x = WINDOW_WIDTH - PLAYER_WIDTH;

    
}

void Player::Background()
{
    SDL_RenderCopy(renderer, texture, NULL, &background_rect);
    SDL_RenderDrawRect(renderer,&background_rect);
}
bool Player::Collision(Position bullet)
{
    int BULLET_HEIGHT = 27;
    int bullet_left = bullet.x;
    int bullet_right = bullet.x + BULLET_HEIGHT;
    int bullet_top= bullet.y;
    int bullet_bottom = bullet.y + BULLET_HEIGHT;

    int player_left = position.x;
    int player_right = position.x + PLAYER_WIDTH;
    int player_top = position.y;
    int player_bottom = position.y + PLAYER_HEIGHT;

    if (bullet_bottom <= player_bottom && bullet_top >= player_top && (bullet_right >= player_left && bullet_left <= player_right)) return 1;
    //if(bullet_bottom >= player_top && bullet_left ==player_right) return 1;
    return 0;
}
Player::~Player()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(spaceship);
    //SDL_FreeSurface(sky);
}