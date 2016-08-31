// Grimorik Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
void gameLoop( WorldInfo *world_info)
{
   int cameraX = 0;
   int cameraY = 0;

   SDL_Surface *screen, *temp, *sprite;

   float rectCoordX = 0, rectCoordY = 0;

   Uint32 ticks;
   Uint32 seconds;
   float prev = 0, cur, dt = 0;

   GameObject *temp_player;
   temp_player = new GameObject(0, 0, 0, 120, 120, world_info);
   temp_player->setImage("materials/test/noct.bmp");

   GameObject *temp_player_static;
   temp_player_static = new GameObject(0, 0, 0, 120, 120, world_info);
   temp_player_static->setImage("materials/test/noct.bmp");
   while (1) {
      ticks = SDL_GetTicks();
      seconds = ticks / 1000;
      dt = ticks - prev;
      float dtsec = dt / 1000;
      prev = ticks;

      SDL_Event e;
      if (SDL_PollEvent(&e)) {
         /* an event was found */
         switch (e.type) {
            /* close button clicked */
            case SDL_QUIT:
               return;
               break;
            /* handle the keyboard */
            case SDL_KEYDOWN:
               switch (e.key.keysym.sym) {
                  case SDLK_ESCAPE:
                  return;
                  break;
               }
               break;
         }

      }


      const Uint8* keystate = SDL_GetKeyboardState(NULL);

      glm::vec2 playerVel = glm::vec2(0,0);

      //continuous-response keys
      if (keystate[SDL_SCANCODE_A])
      {
         playerVel.x = -200;
         std::cout << temp_player->getWorldX() << "\n";
         std::cout << world_info->cameraPosX << "\n";
         std::cout << temp_player->getScreenX() << "\n";
      }
      if (keystate[SDL_SCANCODE_D])
      {
         playerVel.x = 200;
         std::cout << temp_player->getWorldX() << "\n";
         std::cout << world_info->cameraPosX << "\n";
         std::cout << temp_player->getScreenX() << "\n";
      }
      if (keystate[SDL_SCANCODE_W])
      {
         playerVel.y = -200;
         std::cout << temp_player->getWorldY() << "\n";
         std::cout << world_info->cameraPosY << "\n";
         std::cout << temp_player->getScreenY() << "\n";
      }
      if (keystate[SDL_SCANCODE_S])
      {
         playerVel.y = 200 ;
         std::cout << temp_player->getWorldY() << "\n";
         std::cout << world_info->cameraPosY << "\n";
         std::cout << temp_player->getScreenY() << "\n";
      }
   
      rectCoordX += playerVel.x *dtsec;
      rectCoordY += playerVel.y *dtsec;


      temp_player->setWorldPos((int)rectCoordX, (int)rectCoordY);
         
      // THIS SECTION DEALS WITH SPRINGY CAMERA 
      float ks = 1; // spring constant
      glm::vec2 L = glm::vec2(temp_player->getWorldX() - world_info->cameraPosX, temp_player->getWorldY() - world_info->cameraPosY);
      float r = 60; // resting length
      float dist = std::abs(glm::length(L));
      glm::vec2 dv = glm::vec2(-playerVel.x + world_info->cameraVelocity.y, -playerVel.y + world_info->cameraVelocity.y);
      float kd = 5; // damping constant
      if (dist > r)
      {
         std::cout << " here\n";
         glm::vec2 force = -((ks * (glm::length(L) - r) + kd * (glm::dot(dv, (L)))) / glm::length(L)) * (L * (1.0f / glm::length(L)));

         float mass = 10.0;

         glm::vec2 F1 = -ks * (dist - r) * (glm::normalize(L) * (1.0f / dist)) - kd * (dv);
         std::cout << force.x << "\n";
         std::cout << force.y << "\n";
         F1 = -F1;
         world_info->cameraVelocity.x += F1.x * dtsec / mass;
         world_info->cameraVelocity.y += F1.y * dtsec / mass;
      }

      world_info->cameraPosX += (int)world_info->cameraVelocity.x * dtsec;
      world_info->cameraPosY += (int)world_info->cameraVelocity.y * dtsec;
      // END SPRINGY CAMERA 

      // clears the screen
      SDL_SetRenderDrawColor(world_info->renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderClear(world_info->renderer);

      // creates test rectangle to render to
      
      temp_player->render();
      temp_player_static->render();
      SDL_RenderPresent(world_info->renderer);
   }
}



int main(int argc, char* argv[])
{
   WorldInfo *world_info = new WorldInfo;
   int posX = 100, posY = 100, width = 800, height = 600;

   world_info->cameraPosX = 0;
   world_info->cameraPosY = 0;
   world_info->screenWidth = 800;
   world_info->screenHeight = 600;
   world_info->cameraVelocity = glm::vec3(0, 0, 0);
   SDL_Init(SDL_INIT_VIDEO);

   world_info->win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

   world_info->renderer = SDL_CreateRenderer(world_info->win, -1, SDL_RENDERER_ACCELERATED);

   gameLoop(world_info);

   SDL_DestroyRenderer(world_info->renderer);
   SDL_DestroyWindow(world_info->win);

   SDL_Quit();

   return 0;
}