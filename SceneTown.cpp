#include "Scenes.h"
#include "NPC.h"
#include  <vector>
#include <algorithm>    // std::sort
#include <iostream>
SceneTown::SceneTown()
{

}

SceneTown::~SceneTown()
{

}



void SceneTown::setup(WorldInfo *world)
{

   world->dialogueFont = TTF_OpenFont("c:/Windows/Fonts/KELMSCOT.ttf", 24); //this opens a font style and sets a size
   if (!world->dialogueFont) {
      printf("TTF_OpenFont: %s\n", TTF_GetError());
      // handle error
   }

   world_info = world;

   GameObject *temp_bg = new GameObject(0, 0, -3, 1024, 1024, world_info);
   temp_bg->setImage("materials/test/bg.png");
   world_info->objects = std::vector<GameObject *>();
   temp_bg->addToDrawList();;

   temp_player = new PlayerObject(0, 0, 0, 80, 80, world_info);
   temp_player->setImage("materials/test/noct.png");
   temp_player->addToDrawList();
   temp_player->offSetBBox(0, temp_player->getHeight() / 2, -1 , temp_player->getHeight() / 2);
   world_info->player = temp_player;
  
   std::vector<NPC *> npcs = NPCLoader("NPC_database.txt", world_info);
   for (int i = 0; i < npcs.size(); i++)
   {
      npcs.at(i)->addToDrawList();
   }


   world_info->collideables.push_back(temp_player);
   world_info->collideables.insert(world_info->collideables.end(), npcs.begin(), npcs.end());   
}

bool pause = false;

int SceneTown::processControl(float dt)
{
   SDL_Event e;
   if (SDL_PollEvent(&e)) {
      /* an event was found */
      switch (e.type) {
         /* close button clicked */
      case SDL_QUIT:
         return -1;
         break;
         /* handle the keyboard */
      case SDL_KEYDOWN:
         switch (e.key.keysym.sym) {
         case SDLK_ESCAPE:
            return -1;
            break;
         case SDLK_SPACE:
            pause = !pause;
            break;
         }
         break;

      }
   }

   

   world_info->keystates = SDL_GetKeyboardState(NULL);
   
   //continuous-response keys SEND INPUT TO PLAYER CLASS TO HANDLE MOVEMENT
   if (world_info->keystates[SDL_SCANCODE_E])
   {
      for (int i = 0; i < world_info->objects.size();i++)
      {
         NPC *other;
         if ((other = dynamic_cast<NPC *> (world_info->objects.at(i))) != 0)
         {
            if (distanceOfGO(other, temp_player) < 100 && other->isInteracting == false) {
               other->interact();
            }
         }
      }
   }

   return 1;
}

void SceneTown::update(float dt)
{
  
   if (pause == true)
      return;

  
   rectCoordX += playerVel.x * dt;
   rectCoordY += playerVel.y * dt;

   world_info->cameraPosX = (int)temp_player->getWorldX();
   world_info->cameraPosY = (int)temp_player->getWorldY();

   for (int i = 0; i < world_info->objects.size(); i++)
   {
      world_info->objects.at(i)->update(dt);
   }

   std::sort(world_info->objects.begin(), world_info->objects.end(), isFirstGameObject);
}


#include <fstream>

void SceneTown::render(float dt)
{
     
   for (int i = 0; i < world_info->objects.size(); i++)
   {
      world_info->objects.at(i)->render();
   }
      
   SDL_RenderPresent(world_info->renderer);
}