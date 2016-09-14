#include "AreaPortal.h"
#include "PlayerObject.h"
AreaPortal::AreaPortal(int x, int y, int z, int w, int h, WorldInfo *info): 
   CollideableObject(x, y, z, w, h, info)
{

}
void AreaPortal::render() {
  // CollideableObject::render();
}
void AreaPortal::update(float dt) {
   


   for (int i = 0; i < info_ptr->collideables.size(); i++)
   {
      if (info_ptr->collideables.at(i) != this)
      {

         BoundingBox *bbox2 = info_ptr->collideables.at(i)->getBBox();
         float d1x = (bbox2->x + bbox2->offsetx - bbox2->w / 2) - (bbox->x + bbox->offsetx + bbox->w / 2);
         float d1y = (bbox2->y + bbox2->offsety - bbox2->h / 2) - (bbox->y + bbox->offsety + bbox->h / 2);
         float d2x = (bbox->x + bbox->offsetx - bbox->w / 2) - (bbox2->x + bbox2->offsetx + bbox2->w / 2);
         float d2y = (bbox->y + bbox->offsety - bbox->h / 2) - (bbox2->y + bbox2->offsety + bbox2->h / 2);

         float smallest = d1x;

         //   std::cout << d1x << " " << d1x << " " << d2x << " " << d2y << "\n";
         if (d1x > 0.0f || d1y > 0.0f)
         {

         }
         else if (d2x > 0.0f || d2y > 0.0f)
         {
         }
         else
         {
            if (d2x > -3 && info_ptr->player->getVelX() < 0)
               info_ptr->curScene = nextScene;
            if (d1x  > -3 && info_ptr->player->getVelX() > 0)
               info_ptr->curScene = nextScene;
            if (d2y > -3 && info_ptr->player->getVelY() < 0)
            {
               info_ptr->curScene = nextScene;
            }
            if (d1y > -3 && info_ptr->player->getVelY() > 0)
            {
               info_ptr->curScene = nextScene;
            }
         }
        
      }
   }

   
}

void AreaPortal::addToDrawList()
{
   // do nothing since we don't want this to be visualized
}
void AreaPortal::removeFromDrawList()
{
   // do nothing since we don't want this to be visualized
}