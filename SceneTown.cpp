#include "Scenes.h"
#include "NPC.h"
#include  <vector>
#include <algorithm>    // std::sort
#include <iostream>

SceneTown::SceneTown()
{
   sceneName = "outsideInTown";
}

SceneTown::~SceneTown()
{

}



void SceneTown::setup(WorldInfo *world)
{
   if (setupCalled)
      return;
   setupCalled = true;




   world->dialogueFont = TTF_OpenFont("c:/Windows/Fonts/KELMSCOT.ttf", 24); //this opens a font style and sets a size
   if (!world->dialogueFont) {
      printf("TTF_OpenFont: %s\n", TTF_GetError());
      // handle error
   }

   world_info = world;

   sceneObjects = std::vector<GameObject *>();
   sceneCollideables = std::vector<CollideableObject *>();

   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

   GameObject *temp_bg = new GameObject(0, 0, -3, 1024, 1024, world_info);
   temp_bg->setImage("materials/test/bg.png");
   temp_bg->addToDrawList();;

   temp_player = new PlayerObject(0, 0, 0, 80, 80, world_info);
   temp_player->setImage("materials/test/noct.png");
   temp_player->addToDrawList();
   temp_player->addToCollisionList();
   temp_player->offSetBBox(0, temp_player->getHeight() / 2, -1 , temp_player->getHeight() / 2);
   world_info->player = temp_player;

   CollideableObject *house = new CollideableObject(0, -740, 0, 512, 512, world_info);
   house->setImage("materials/test/temphouse.png");
   house->addToDrawList();
   house->addToCollisionList();
  
   std::vector<NPC *> npcs = NPCLoader("NPC_database.txt", world_info);
   for (int i = 0; i < npcs.size(); i++)
   {
      npcs.at(i)->addToDrawList();
      npcs.at(i)->addToCollisionList();
   }
   


   nextAreaPortal = new AreaPortal(0, -500, 0, 100, 60, world_info);
   SceneInside *nextScene = new SceneInside();
   nextAreaPortal->setNextScene("insideTownCave", "caveDoorway1");
   world_info->collideables->push_back(nextAreaPortal);
   nextAreaPortal->addToDrawList();
}

bool pause = false;

int SceneTown::processControl(float dt)
{
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

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
      for (int i = 0; i < sceneObjects.size();i++)
      {
         NPC *other;
         if ((other = dynamic_cast<NPC *> (sceneObjects.at(i))) != 0)
         {
            if (distanceOfGO(other, world_info->player) < 100 && other->isInteracting == false) {
               other->interact();
            }
         }
      }
   }

   return 1;
}

void SceneTown::update(float dt)
{
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

   if (pause == true)
      return;

  
   //   nextAreaPortal->update(dt);
   world_info->cameraPosX = (int)world_info->player->getWorldX();
   world_info->cameraPosY = (int)world_info->player->getWorldY();

   for (int i = 0; i < world_info->objects->size(); i++)
   {
      world_info->objects->at(i)->update(dt);
   }

   std::sort(world_info->objects->begin(), world_info->objects->end(), isFirstGameObject);
}

void SceneTown::EnterScene(std::string loc)
{
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;




   world_info->curScene = this;
   if (loc == "caveDoorway1")
   {
      world_info->player->setWorldPos(0, -450);
      world_info->player->addToDrawList();
      world_info->player->addToCollisionList();
    //  world_info->collideables->push_back(world_info->player);

   }
}


#include <fstream>

void SceneTown::render(float dt)
{

   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;
   std::cout << "here1\n";
   for (int i = 0; i < world_info->objects->size(); i++)
   {
      world_info->objects->at(i)->render();
   }
      
   SDL_RenderPresent(world_info->renderer);
}

SceneInside::SceneInside()
{
   sceneName = "insideTownCave";
}

SceneInside::~SceneInside()
{

}



void SceneInside::setup(WorldInfo *world)
{
   if (setupCalled)
      return;
   setupCalled = true;


   world->dialogueFont = TTF_OpenFont("c:/Windows/Fonts/KELMSCOT.ttf", 24); //this opens a font style and sets a size
   if (!world->dialogueFont) {
      printf("TTF_OpenFont: %s\n", TTF_GetError());
      // handle error
   }


   sceneObjects = std::vector<GameObject *>();
   sceneCollideables = std::vector<CollideableObject *>();


   world_info = world;
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

   GameObject *temp_bg = new GameObject(0, 0, -3, 1024, 1024, world_info);
   temp_bg->setImage("materials/test/insidefloor.png");
   temp_bg->addToDrawList();

   CollideableObject *wall = new CollideableObject(0, -512, -2, 1024, 257, world_info);
   wall->setImage("materials/test/backwall.png");
   wall->addToDrawList();
   wall->offSetBBox(0, 0, -1, wall->getHeight() / 2);
   world_info->collideables->push_back(wall);

   
   wall = new CollideableObject(0, 512, -2, 1024, 144, world_info);
   wall->setImage("materials/test/wall_front.png");
   wall->addToDrawList();
   wall->offSetBBox(0, wall->getHeight() / 3, -1, wall->getHeight() / 2);
   world_info->collideables->push_back(wall);

   wall = new CollideableObject(512, 0, -2, 142, 1024, world_info);
   wall->setImage("materials/test/wall_right.png");
   wall->addToDrawList();
   wall->offSetBBox(0, 0, wall->getWidth() / 3, -1);
   world_info->collideables->push_back(wall);

   wall = new CollideableObject(-512, 0, -2, 142, 1024, world_info);
   wall->setImage("materials/test/wall_left.png");
   wall->addToDrawList();
   wall->offSetBBox(0, 0, wall->getWidth() / 3, -1);
   world_info->collideables->push_back(wall);
   
   //world_info->player->addToDrawList();
 //  world_info->collideables->push_back(world_info->player);


   nextAreaPortal = new AreaPortal(0, 500, 0, 100, 60, world_info);
 //  SceneInside *nextScene = new SceneInside();
   nextAreaPortal->setNextScene("outsideInTown", "caveDoorway1");

}


void SceneInside::EnterScene(std::string loc)
{
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

   world_info->curScene = this;
   if (loc == "caveDoorway1")
   {
      world_info->player->setWorldPos(0, 450);
      world_info->player->addToDrawList();
      world_info->player->addToCollisionList();
   }
}

int SceneInside::processControl(float dt)
{
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

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
      for (int i = 0; i < world_info->objects->size();i++)
      {
         NPC *other;
         if ((other = dynamic_cast<NPC *> (world_info->objects->at(i))) != 0)
         {
            if (distanceOfGO(other, world_info->player) < 100 && other->isInteracting == false) {
               other->interact();
            }
         }
      }
   }
   nextAreaPortal->update(dt);
   return 1;
}

void SceneInside::update(float dt)
{
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

   if (pause == true)
      return;


   world_info->cameraPosX = (int)world_info->player->getWorldX() ;
   world_info->cameraPosY = (int)world_info->player->getWorldY();

   for (int i = 0; i < world_info->objects->size(); i++)
   {
      world_info->objects->at(i)->update(dt);
   }

   std::sort(world_info->objects->begin(), world_info->objects->end(), isFirstGameObject);
}


void SceneInside::render(float dt)
{

   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;

   for (int i = 0; i < world_info->objects->size(); i++)
   {
      world_info->objects->at(i)->render();
   }

   SDL_RenderPresent(world_info->renderer);
}