#include "Scenes.h"
#include <iostream>
AreaTransition::AreaTransition()
{
   timeelapsed = 0;
}

void AreaTransition::setup(WorldInfo *world)
{
   world_info = world;
   blackOverlay = new GameObject(world->player->getWorldX(), world->player->getWorldY(), 100, world->screenWidth, world->screenHeight, world);
   blackOverlay->setColor(0, 0, 0, 0);
   world->scenes.push_back(this);
   timeelapsed = 0;
}
int AreaTransition::processControl(float dt)
{
   return 0;
   // can't do anything while scene is in transtition
}
void AreaTransition::update(float dt)
{
   timeelapsed += dt;
   float normedtime;

   blackOverlay->setWorldPos(world_info->player->getWorldX(), world_info->player->getWorldY());

   if (cur == from) {
      normedtime = timeelapsed / 0.5;
      blackOverlay->setColor(0, 0, 0, 255 * normedtime);
   } 
   if (cur == to) {
      normedtime = timeelapsed / 0.5f;
      blackOverlay->setColor(0, 0, 0, 255 * (1 - normedtime));
   }

   if (normedtime > 1 && cur == from)
   {
      cur = to;
      timeelapsed = 0;
      from->exitingScene();
      to->EnterScene(entryPoint);
   }

   else if(normedtime > 1 && cur == to)
   {
      timeelapsed = 0;
      world_info->curScene = to;
      for (int i = 0; i < world_info->scenes.size(); i++)
      {
         if (this == world_info->scenes.at(i))
            world_info->scenes.erase(world_info->scenes.begin() + i);
      }
      world_info->pause = false;
   }
}
void AreaTransition::render(float dt)
{

   std::cout << "here\n";
   
   cur->render(dt);
   blackOverlay->addToDrawList();
}
void AreaTransition::setScenes(GameScene *f, GameScene *t)
{
   cur = f;
   from = f;
   to = t;
}

void AreaTransition::EnterScene(std::string in)
{
   entryPoint = in;
}