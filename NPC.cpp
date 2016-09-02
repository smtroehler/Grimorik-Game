#include "NPC.h"
#include "States.h"
#include <iostream>

NPC::NPC(int x, int y, int z, int w, int h, WorldInfo *info) :
   GameObject(x, y, z, w, h, info)
{

   has_quest_symbol = new GameObject(x, y - (h / 2) - 35 , 0, 40, 40, info);
   has_quest_symbol->setImage("materials/interaction/exclemation.png");
   has_quest_symbol->setVelocity(0, 50, 0);

   State *moveLeft, *stop_p1, *moveRight, *stop_p2;
   moveLeft = new MoveToState(this, NULL, glm::vec3(0, 0, 0), 50);
   moveRight = new MoveToState(this, NULL, glm::vec3(600, 0, 0), 50);
   stop_p1 = new WaitState(this, 2.0f, NULL);
   stop_p2 = new WaitState(this, 2.0f, NULL);

   curState = moveLeft;
   moveLeft->setNextState(stop_p1);
   stop_p1->setNextState(moveRight);
   moveRight->setNextState(stop_p2);
   stop_p2->setNextState(moveLeft);
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
      has_quest_symbol->setWorldPos(worldX, has_quest_symbol->getWorldY());
      float miny = worldY - (height / 2) - 35;
      float maxy = worldY - (height / 2) - 45;
      float cury = has_quest_symbol->getWorldY();

      float normd_dist = ((cury - maxy) / 10);
      if (normd_dist < 0.00001)
      {
         has_quest_symbol->setVelocity(velX, 35 + velY, 0);
      }
      else if (normd_dist > .9999)
      {
         has_quest_symbol->setVelocity(velX, -35 + velY, 0);
      }

     
      has_quest_symbol->update(dt);
   }

   curState = curState->update(dt);
   

   GameObject::update(dt);
}


void NPC::interact() {
   if (isInteractionFinished == false)
      return;

   prevVelocity = getVelocity();
   isInteractionFinished = false;
   setVelocity(0, 0, 0);
   std::cout << "I have a quest for you!\n";
   hasQuest = false;
}

void NPC::interactionFinished() {

   setVelocity(prevVelocity);
   isInteractionFinished = true;
}

