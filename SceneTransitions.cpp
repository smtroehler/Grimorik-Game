#include "Scenes.h"
#include <iostream>
AreaTransition::AreaTransition()
{
   timeelapsed = 0;
   fadeOut = .25;
   fadeIn = .25;
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
            world_info->pause = world_info->pause;
            break;
         }
         break;

      }
   }
   
   return 0;
   
}
void AreaTransition::update(float dt)
{
   if(cur == from)
      world_info->player_input_disabled = true;

   timeelapsed += dt;
   float normedtime;

   blackOverlay->setWorldPos(world_info->player->getWorldX(), world_info->player->getWorldY());

   if (cur == from) {
      normedtime = timeelapsed / fadeOut;
      blackOverlay->setColor(0, 0, 0, 255 * normedtime);
   } 
   if (cur == to) {
      normedtime = timeelapsed / fadeIn;
      blackOverlay->setColor(0, 0, 0, 255 * (1 - normedtime));
   }

   if (normedtime > 1 && cur == from)
   {
      cur = to;
      timeelapsed = 0;
      from->exitingScene();
      to->EnterScene(entryPoint);
      world_info->player_input_disabled = false;
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
      
   }
}
void AreaTransition::render(float dt)
{
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