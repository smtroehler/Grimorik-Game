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


DialogueBox *test;
DialogueScene *testscene;
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
   objects = std::vector<GameObject *>();
   objects.push_back(temp_bg);
   temp_player = new GameObject(0, 0, 0, 80, 80, world_info);
   temp_player->setImage("materials/test/noct.png");
   objects.push_back(temp_player);

  
   NPC *temp_npc = new NPCTEST(500, 0, 0, 80, 80, world_info);
   temp_npc->setImage("materials/test/noct.png");
   objects.push_back(temp_npc);

   std::vector<NPC *> npcs = NPCLoader("NPC_database.txt", world_info);
   objects.insert(objects.end(), npcs.begin(), npcs.end());

   testscene = new DialogueScene(world_info);
   test = new DialogueBox(world_info, glm::vec3(0, 0, 0), "hello tehre testing new lines");
   test->setTalkingSprite("materials/test/noct.png");
   test->addLineOfText("this is on a new line");
   
   testscene->addDialogueBox(test);

   test = new DialogueBox(world_info, glm::vec3(0, 0, 0), "this is a test of multiple dialogs");
   test->setTalkingSprite("materials/test/noct.png");
   test->addLineOfText("character is aligned on the other side");
   test->alignLeft();

   testscene->addDialogueBox(test);

   test = new DialogueBox(world_info, glm::vec3(0, 0, 0), "this is a third test");
   test->setTalkingSprite("materials/test/noct.png");
   test->addLineOfText("here we will test a third line");
   test->addLineOfText("here is the third line");
   test->alignRight();

   testscene->addDialogueBox(test);
   
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

   isMovingX = false;
   isMovingY = false;

   //continuous-response keys SEND INPUT TO PLAYER CLASS TO HANDLE MOVEMENT
   if (world_info->keystates[SDL_SCANCODE_A])
   {
      playerVel.x = -300;
      isMovingX = true;
   }
   if (world_info->keystates[SDL_SCANCODE_D])
   {
      playerVel.x = 300;
      isMovingX = true;
   }
   if (world_info->keystates[SDL_SCANCODE_W])
   {
      playerVel.y = -300;
      isMovingY = true;
   }
   if (world_info->keystates[SDL_SCANCODE_S])
   {
      playerVel.y = 300;
      isMovingY = true;
   }
   if (world_info->keystates[SDL_SCANCODE_E])
   {
      for (int i = 0; i < objects.size();i++)
      {
         NPC *other;
         if ((other = dynamic_cast<NPC *> (objects.at(i))) != 0)
         {
            if (distanceOfGO(other, temp_player) < 100) {
               other->interact();
            }
         }
      }
   }


   return 1;
}

void SceneTown::update(float dt)
{
   testscene->update(dt);
   if (pause == true)
      return;

   if (isMovingX == false)
   {
      playerVel.x += 15 * -playerVel.x * dt;
   }

   if (isMovingY == false)
   {
      playerVel.y += 15 * -playerVel.y * dt;
   }
   rectCoordX += playerVel.x * dt;
   rectCoordY += playerVel.y * dt;

   temp_player->setWorldPos((int)rectCoordX, (int)rectCoordY);

   glm::vec2 dif = glm::vec2(rectCoordX - world_info->cameraPosX, rectCoordY - world_info->cameraPosY);

   world_info->cameraPosX = (int)rectCoordX;
   world_info->cameraPosY = (int)rectCoordY;

   std::sort(objects.begin(), objects.end(), isFirstGameObject);

   for (int i = 0; i < objects.size(); i++)
   {
      objects.at(i)->update(dt);
   }
}


#include <fstream>

void SceneTown::render(float dt)
{
   

   

  
   for (int i = 0; i < objects.size(); i++)
   {
      objects.at(i)->render();
   }
      


   if(testscene->toRender() != NULL)
      testscene->toRender()->render();


   SDL_RenderPresent(world_info->renderer);
}