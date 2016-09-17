// Grimorik Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <cstring>
#include <vector>
void gameLoop( WorldInfo *world_info)
{
   int cameraX = 0;
   int cameraY = 0;

   SDL_Surface *screen, *temp, *sprite;

   float rectCoordX = 0, rectCoordY = 0;

   Uint32 ticks;
   float seconds;
   float prev = 0, cur, dt = 0.0f;

   // create the town scene and make it the current scene
   GameScene *scene1 = new SceneTown();
   scene1->setup(world_info);
   world_info->curScene = scene1;
   world_info->scenes.push_back(scene1);

   // create the cave scene
   scene1 = new SceneInside();
   scene1->setup(world_info);
   world_info->scenes.push_back(scene1);

   while (1) {

      const Uint8* keystate = SDL_GetKeyboardState(NULL);


      
      ticks = SDL_GetTicks();
      seconds = (float) ticks / 1000.0f;
      dt = ticks - prev;
      float dtsec = dt / 1000.0f;
      
      //make sure the time slice isn't huge for whatever reason
      if (dtsec > .003)
         dtsec = .001;

      prev = ticks;
      
      if (world_info->curScene->processControl(dtsec) == -1)
         return;

      for (int i = 0; i < world_info->scenes.size(); i++)
      {
         world_info->scenes.at(i)->update(dtsec);
      }
      

      // clears the screen
      SDL_SetRenderDrawColor(world_info->renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderClear(world_info->renderer);

   
      world_info->curScene->render(dtsec);
      
   }
}



int main(int argc, char* argv[])
{
   WorldInfo *world_info = new WorldInfo;
   int posX = 100, posY = 100, width = 1200, height = 900;

   world_info->cameraPosX = 0;
   world_info->cameraPosY = 0;
   world_info->screenWidth = 1200;
   world_info->screenHeight = 900;
   world_info->cameraVelocity = glm::vec3(0, 0, 0);
   world_info->cameraAccel = glm::vec3(0, 0, 0);
   world_info->pause = false;
   world_info->player_input_disabled = false;

   TTF_Init();
   SDL_Init(SDL_INIT_VIDEO);

   world_info->win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

   world_info->renderer = SDL_CreateRenderer(world_info->win, -1, SDL_RENDERER_ACCELERATED);

   gameLoop(world_info);

   SDL_DestroyRenderer(world_info->renderer);
   SDL_DestroyWindow(world_info->win);

   SDL_Quit();

   return 0;
}