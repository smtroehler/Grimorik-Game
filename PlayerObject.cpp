#include "PlayerObject.h"

#include <iostream>
PlayerObject::PlayerObject(int x, int y, int z, int w, int h, WorldInfo *info) :
   CollideableObject(x, y, z, w, h, info) {
   isInteracting = false;
}

void PlayerObject::render()
{
   CollideableObject::render();
}
void PlayerObject::update(float dt)
{
   if (info_ptr->player_input_disabled)
      return;
     
   bool isMovingX = false, isMovingY = false;
   float velocity = 300;
   glm::vec2 dir = glm::vec2(0,0);
   if (info_ptr->keystates[SDL_SCANCODE_A])
   {
      dir.x = -1;
      isMovingX = true;
   }
   if (info_ptr->keystates[SDL_SCANCODE_D])
   {
      dir.x = 1;
      isMovingX = true;
   }
   if (info_ptr->keystates[SDL_SCANCODE_W])
   {
      dir.y = -1;
      isMovingY = true;
   }
   if (info_ptr->keystates[SDL_SCANCODE_S])
   {
      dir.y = 1;
      isMovingY = true;
   }
   if (dir.x || dir.y) {
      dir = glm::normalize(dir);
      velX = dir.x * 300;
      velY = dir.y * 300;
   }

   if (isMovingX == false)
   {
      velX += 15.0f * -velX * dt;
   }

   if (isMovingY == false)
   {
      velY += 15.0f * -velY * dt;
   }

   if (isInteracting)
      velX = velY = 0;

   CollideableObject::update(dt);
}

void PlayerObject::addToDrawList()
{
   CollideableObject::addToDrawList();
}
void PlayerObject::removeFromDrawList()
{
   CollideableObject::removeFromDrawList();
}