#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Window.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <vector>
#include <chrono>
#pragma once
using namespace std;

void Fill_Enemies(vector <Player*> enemies,Window* window);