#include "PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, int z, int w, int h, WorldInfo *info) :
   CollideableObject(x, y, z, w, h, info) {

}

void PlayerObject::render()
{
   CollideableObject::render();
}
void PlayerObject::update(float dt)
{
   bool isMovingX = false, isMovingY = false;
   if (info_ptr->keystates[SDL_SCANCODE_A])
   {
      velX = -300;
      isMovingX = true;
   }
   if (info_ptr->keystates[SDL_SCANCODE_D])
   {
      velX = 300;
      isMovingX = true;
   }
   if (info_ptr->keystates[SDL_SCANCODE_W])
   {
      velY = -300;
      isMovingY = true;
   }
   if (info_ptr->keystates[SDL_SCANCODE_S])
   {
      velY = 300;
      isMovingY = true;
   }


   if (isMovingX == false)
   {
      velX += 15.0f * -velX * dt;
   }

   if (isMovingY == false)
   {
      velY += 15.0f * -velY * dt;
   }

   CollideableObject::update(dt);
}