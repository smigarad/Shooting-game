#include "Functions.hpp"

void Fill_Enemies(vector <Player*> enemies,Window* window)
{
    for (uint i = 0; i < 4; i++)
    {
        enemies.emplace_back(new Player({1000,-200}, window->renderer,"enemy_space2.png"));
    }
}