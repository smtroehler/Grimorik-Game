#include "AreaPortal.h"
#include "PlayerObject.h"

#include <iostream>
AreaPortal::AreaPortal(int x, int y, int z, int w, int h, WorldInfo *info): 
   Triggers(x, y, z, w, h, info)
{
   isSolid = false;
}
void AreaPortal::render() {
  // CollideableObject::render();
}

void AreaPortal::transitionToScene()
{

   for (int i = 0; i < info_ptr->scenes.size(); i++)
   {
      if (info_ptr->scenes.at(i)->getName() == nextScene) {
         info_ptr->curScene->exitingScene();
         info_ptr->scenes.at(i)->EnterScene(entryPoint);
      }
   }
   timeExisting = 0;
   playerStartsInBox = false;
}

void AreaPortal::update(float dt) {
   timeExisting += dt;
   

      if (info_ptr->player != NULL)
      {

         BoundingBox *bbox2 = info_ptr->player->getBBox();
         float d1x = (bbox2->x + bbox2->offsetx - bbox2->w / 2) - (bbox->x + bbox->offsetx + bbox->w / 2);
         float d1y = (bbox2->y + bbox2->offsety - bbox2->h / 2) - (bbox->y + bbox->offsety + bbox->h / 2);
         float d2x = (bbox->x + bbox->offsetx - bbox->w / 2) - (bbox2->x + bbox2->offsetx + bbox2->w / 2);
         float d2y = (bbox->y + bbox->offsety - bbox->h / 2) - (bbox2->y + bbox2->offsety + bbox2->h / 2);

         if (d1x > 0.0f || d1y > 0.0f)
         {
           
            playerStartsInBox = false;
         }
         else if (d2x > 0.0f || d2y > 0.0f)
         {
            playerStartsInBox = false;
         }
         else
         {

            if (timeExisting < .5)
            {
               playerStartsInBox = true;
            }
            if(!playerStartsInBox)
               transitionToScene();
         }
        
      }
}

void AreaPortal::addToDrawList()
{
   CollideableObject::addToDrawList();
}
void AreaPortal::removeFromDrawList()
{
   CollideableObject::removeFromDrawList();
}