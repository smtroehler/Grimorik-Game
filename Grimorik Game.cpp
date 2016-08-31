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
   float seconds;
   float prev = 0, cur, dt = 0.0f;

   GameObject *temp_player;
   temp_player = new GameObject(0, 0, 0, 80, 80, world_info);
   temp_player->setImage("materials/test/noct.bmp");

   GameObject *temp_player_static;
   temp_player_static = new GameObject(0, 0, 0, 120, 120, world_info);
   temp_player_static->setImage("materials/test/noct.bmp");
   while (1) {
      ticks = SDL_GetTicks();
      seconds = (float) ticks / 1000.0f;
      dt = ticks - prev;
      float dtsec = dt / 1000.0f;
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

      static glm::vec2 playerVel = glm::vec2(0,0);
      bool isMovingX = false, isMovingY = false;
      //continuous-response keys
      if (keystate[SDL_SCANCODE_A])
      {
         
         playerVel.x = -300;
         isMovingX = true;
      }
      if (keystate[SDL_SCANCODE_D])
      {
         playerVel.x = 300;
         isMovingX = true;
      }
      if (keystate[SDL_SCANCODE_W])
      {
         playerVel.y = -300;
         isMovingY = true;
      }
      if (keystate[SDL_SCANCODE_S])
      {
         playerVel.y = 300;
         isMovingY = true;
      }
      
      if (isMovingX == false)
      {
         playerVel.x += 15 * -playerVel.x * dtsec;
      }

      if (isMovingY == false)
      {
         playerVel.y += 15 * -playerVel.y * dtsec;
      }
      rectCoordX += playerVel.x * dtsec;
      rectCoordY += playerVel.y * dtsec;

      temp_player->setWorldPos((int)rectCoordX, (int)rectCoordY);

      glm::vec2 dif = glm::vec2(rectCoordX - world_info->cameraPosX, rectCoordY - world_info->cameraPosY);
     
      world_info->cameraPosX = (int)rectCoordX;
      world_info->cameraPosY = (int)rectCoordY;
      
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
   world_info->cameraAccel = glm::vec3(0, 0, 0);
   
   SDL_Init(SDL_INIT_VIDEO);

   world_info->win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

   world_info->renderer = SDL_CreateRenderer(world_info->win, -1, SDL_RENDERER_ACCELERATED);

   gameLoop(world_info);

   SDL_DestroyRenderer(world_info->renderer);
   SDL_DestroyWindow(world_info->win);

   SDL_Quit();

   return 0;
}