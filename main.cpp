#include "main.hpp"

int main()
{

    Position default_position = {40 , WINDOWS_HEIGHT /2 };
    Window* window = new Window("Shooting game");
    Player* player = new Player (default_position,window->renderer, "spaceship2.png");
    vector <Bullet*> bullets;
    vector <Player*> enemies;
    vector <Bullet*>* bullets_enemy = new vector <Bullet*> [4];
    for (uint i = 0; i < 4; i++)
    {
        enemies.emplace_back(new Player({1000,-200}, window->renderer,"enemy_space2.png"));
    }

    for (uint i =0; i <4; i++)
    {
        for (uint j =0; j < MAX_BULLETS; j++)
        {
            bullets_enemy[i].emplace_back(new Bullet({600,600},window->renderer,"bullet2.png"));
        }
    }

    for(unsigned int i = 0; i < MAX_BULLETS; ++i)
    {
	bullets.emplace_back(new Bullet({300,300},window->renderer,"bullet2.png"));
    }
    int bullets_counter_enemy[4];
    bool down [4] = {1,1,1,1};
    float dt;
    int lvl =1;
    bool run =1;
    bool shot =0;
    bool shot_enemy[4] = {0,0,0,0};
    int bullets_counter =0;
    int delay[4];
    SDL_Event event;
    bool controls[7] = {};
    bool hit=0;
    while (run == 1)
    {
        auto startTime = chrono::high_resolution_clock::now();

        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) run =0;


            else if(event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_w) controls[Movement::KeyUP] =1;
                if (event.key.keysym.sym == SDLK_s) controls[Movement::KeyDown] =1;
                if (event.key.keysym.sym == SDLK_d) controls[Movement::KeyRight] =1;
                if (event.key.keysym.sym == SDLK_a) controls[Movement::KeyLeft] =1;
                if (event.key.keysym.sym == SDLK_SPACE) controls[Movement::KeyRestart] =1;
                if (event.key.keysym.sym == SDLK_ESCAPE) controls[Movement::KeyQuit] =1;
                if (event.key.keysym.sym == SDLK_d) controls[Movement::KeyShoot] = 1; 
            }

            else if(event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_w) controls[Movement::KeyUP] =0;
                if (event.key.keysym.sym == SDLK_s) controls[Movement::KeyDown] =0;
                if (event.key.keysym.sym == SDLK_d) controls[Movement::KeyRight] =0;
                if (event.key.keysym.sym == SDLK_a) controls[Movement::KeyLeft] =0;
                if (event.key.keysym.sym == SDLK_SPACE) controls[Movement::KeyRestart] =0;
                if (event.key.keysym.sym == SDLK_ESCAPE) controls[Movement::KeyQuit] =0;
                if (event.key.keysym.sym == SDLK_d) controls[Movement::KeyShoot] = 0;
            }

            //if(controls[Movement::KeyRight]) player->velocity.x = PLAYER_SPEED;
            //else if(controls[Movement::KeyLeft])  player->velocity.x = -PLAYER_SPEED;
            //else player->velocity.x =0;
            if (controls[Movement::KeyUP]) player->velocity.y = -PLAYER_SPEED;
            else if (controls[Movement::KeyDown]) player->velocity.y = PLAYER_SPEED;
            else player->velocity.y =0;
            if (controls[Movement::KeyShoot]) shot = 1;
            else shot =0;
            if (controls[Movement::KeyRestart]) 
            {
                player->position = default_position;
                for(auto s: bullets) s->position = {0,-100};
                //for(auto s: enemies) s->position = {1000,1000};
                lvl =1;
                for (auto s: bullets_enemy[0]) s->position = {0-100};
                for (auto s: bullets_enemy[1]) s->position = {0-100};
                for (auto s: bullets_enemy[2]) s->position = {0-100};
                for (auto s: bullets_enemy[3]) s->position = {0-100};
            }
            if (controls[Movement::KeyQuit]) run =0;
        }

        for (auto s: bullets) s->Update(dt);
        
        for (auto e: enemies)  if (!lvl) e->Update(dt);
        for (auto s: bullets_enemy[0]) s->Update(-dt);
        for (auto s: bullets_enemy[1]) s->Update(-dt);
        for (auto s: bullets_enemy[2]) s->Update(-dt);
        for (auto s: bullets_enemy[3]) s->Update(-dt);
    
        player->Update(dt);
        player->Background();
        
        

        if (lvl ==1)
        {
            enemies[0]->position.y = 50;
            enemies[1]->position.y = 200;
            enemies[2]->position.y = 320;
            enemies[3]->position.y = 520;
            if(enemies[0]->position.x >= 720) enemies[0]->position.x -=1;
            if(enemies[1]->position.x >= 500) enemies[1]->position.x -=1;
            if(enemies[2]->position.x >= 650) enemies[2]->position.x -=1;
            if(enemies[3]->position.x >= 550) enemies[3]->position.x -=1;
            //enemies.front()->position.x =700;
            if(enemies[1]->position.x <=500) lvl =0;
        }
        
        if (!lvl)
        {
            if (enemies[0]->position.y > WINDOWS_HEIGHT/2 + 160) down[0] =0;
            if (enemies[1]->position.y > WINDOWS_HEIGHT/2+200) down[1] =0;
            if (enemies[2]->position.y > WINDOWS_HEIGHT/2+220) down[2] =0;
            if (enemies[3]->position.y > WINDOWS_HEIGHT/2+200) down[3] =0;
            
            
            if (down[0]) enemies[0]->velocity.y =ENEMY_SPEED+0.1;
            else 
            {
                enemies[0]->velocity.y =-ENEMY_SPEED-0.1;
                if (enemies[0]->position.y <= 40) down[0]= 1;
            }

            if (down[1]) enemies[1]->velocity.y =ENEMY_SPEED-0.1;
            else 
            {
                enemies[1]->velocity.y =-ENEMY_SPEED+0.1;
                if (enemies[1]->position.y <= 15) down[1]= 1;
            }

            if (down[2]) enemies[2]->velocity.y =ENEMY_SPEED;
            else 
            {
                enemies[2]->velocity.y =-ENEMY_SPEED;
                if (enemies[2]->position.y <= 25) down[2]= 1;
            }

            if (down[3]) enemies[3]->velocity.y =ENEMY_SPEED;
            else 
            {
                enemies[3]->velocity.y =-ENEMY_SPEED;
                if (enemies[3]->position.y <= 20) down[3]= 1;
            }
        }

        if (shot) 
        {
            bullets[bullets_counter]->position.x = player->position.x +PLAYER_WIDTH;
            bullets[bullets_counter]->position.y = player->position.y +20;
            bullets_counter++;
            if (bullets_counter ==20) bullets_counter =0;
            shot =0;
        }
        if (!lvl)
        {
            if (shot_enemy[0])
            {
                bullets_enemy[0][bullets_counter_enemy[0]]->position.x = enemies[0]->position.x;
                bullets_enemy[0][bullets_counter_enemy[0]]->position.y = enemies[0]->position.y+20;
                bullets_counter_enemy[0]++;
                if(bullets_counter_enemy[0] ==20) bullets_counter_enemy[0] =0;
                shot_enemy[0] = 0;
            }

            if (shot_enemy[1])
            {
                bullets_enemy[1][bullets_counter_enemy[1]]->position.x = enemies[1]->position.x;
                bullets_enemy[1][bullets_counter_enemy[1]]->position.y = enemies[1]->position.y+20;
                bullets_counter_enemy[1]++;
                if(bullets_counter_enemy[1] ==20) bullets_counter_enemy[1] =0;
                shot_enemy[1] = 0;
            }
            
            if (shot_enemy[2])
            {
                bullets_enemy[2][bullets_counter_enemy[2]]->position.x = enemies[2]->position.x;
                bullets_enemy[2][bullets_counter_enemy[2]]->position.y = enemies[2]->position.y+20;
                bullets_counter_enemy[2]++;
                if(bullets_counter_enemy[2] ==20) bullets_counter_enemy[2] =0;
                shot_enemy[2] = 0;
            }

            /*if (shot_enemy[3])
            {
                bullets_enemy[3][bullets_counter_enemy[3]]->position.x = enemies[3]->position.x;
                bullets_enemy[3][bullets_counter_enemy[3]]->position.y = enemies[3]->position.y+20;
                bullets_counter_enemy[3]++;
                if(bullets_counter_enemy[3] ==20) bullets_counter_enemy[3] =0;
                shot_enemy[3] = 0;
            }*/
        }
        delay[0]++;
        delay[1]++;
        delay[2]++;
        delay[3]++;
        if (delay[0] >=2000)
        {
            delay[0]=0;
            shot_enemy[0] =1;
        }

        if (delay[1] >=1500)
        {
            delay[1]=0;
            shot_enemy[1]=1;
        }

        if (delay[2] >=3000)
        {
            delay[2]=0;
            shot_enemy[2]=1;
        }

        if (delay[3] >=500)
        {
            delay[3]=0;
            shot_enemy[3]=1;
        }
        hit=0;
        uint pom1;
        uint pom2;
        for(uint i=0; i<4; i++)
        {
            for(uint j =0; j<20; j++)
            {
                if(i ==pom1&& j == pom2) break;
                if(player->Collision(bullets_enemy[i][j]->position)&& !hit)
                {
                    hit =1;
                    player->health--;    
                    printf("xd%d %d",i,j);
                    pom1 =i;
                    pom2 =j;
                    
                }
            
            }
        }
        if (player->health ==0) 
        {
            SDL_Delay(1000);
            run =0;
        }
        for (auto s : bullets_enemy[0]) s->Draw();
        for (auto s : bullets_enemy[1]) s->Draw();
        for (auto s : bullets_enemy[2]) s->Draw();
        for (auto s : bullets_enemy[3]) s->Draw();
        for (auto s: bullets) s->Draw();
        for (auto e: enemies) e->Draw();
        player->Draw();
        
        window->Display();
        auto stopTime = chrono::high_resolution_clock::now();
	    dt = chrono::duration<float, chrono::milliseconds::period>(stopTime - startTime).count();
    }
    
    SDL_Quit();
    delete player;
    for (auto s : bullets) delete s;
    bullets.clear();
    for (auto e: enemies) delete e;
    enemies.clear();

     for (uint i =0; i <4; i++)
    {
        for (uint j =0; j < MAX_BULLETS; j++)
        {
            delete bullets_enemy[i][j];
            bullets_enemy[i].clear();
        }
    }
        delete[] bullets_enemy;
    delete window;

    return 0;
}