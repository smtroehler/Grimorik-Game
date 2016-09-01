#include "NPC.h"

#include <iostream>

NPC::NPC(int x, int y, int z, int w, int h, WorldInfo *info) :
   GameObject(x, y, z, w, h, info)
{

   has_quest_symbol = new GameObject(x, y - (h / 2) - 35 , 0, 40, 40, info);
   has_quest_symbol->setImage("materials/interaction/exclemation.png");
   has_quest_symbol->setVelocity(0, 50, 0);
}

void NPC::render()
{
   if (hasQuest)
      has_quest_symbol->render();

   GameObject::render();
}
void NPC::update(float dt)
{
   

   if (hasQuest) {
      float miny = worldY - (height / 2) - 35;
      float maxy = worldY - (height / 2) - 45;
      float cury = has_quest_symbol->getWorldY();

      float normd_dist = ((cury - maxy) / 10);
      if (normd_dist < 0.00001)
      {
         has_quest_symbol->setVelocity(0, 35, 0);
      }
      else if (normd_dist > .9999)
      {
         has_quest_symbol->setVelocity(0, -35, 0);
      }

      has_quest_symbol->setWorldPos(worldX, has_quest_symbol->getWorldY());
      has_quest_symbol->update(dt);

    //  
   }

   worldX += -50 * dt;

   GameObject::update(dt);
}


