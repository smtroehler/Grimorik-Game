#include "States.h"

#include <iostream>
TestNPCState::TestNPCState(NPC *bind)
{
   toMove = bind;
   startPos = bind->getWorldPos();
   toMove->setVelocity(-50, 0, 0);
}

State* TestNPCState::update(float dt)
{
   if (toMove->getWorldPos().x <= 0)
   {
      toMove->setVelocity(50, 0, 0);
   }
   if (toMove->getWorldPos().x > startPos.x)
   {
      toMove->setVelocity(-50, 0, 0);
   }

   return this;
}

WaitState::WaitState(NPC *bind, float timeToWait, State *nextState)
{
   toMove = bind;
   
   this->timeToWait = timeToWait;
   elapsedTime = 0;
   this->nextState = nextState;
}

State* WaitState::update(float dt)
{
   toMove->setVelocity(0, 0, 0);
   elapsedTime += dt;
   if (timeToWait > elapsedTime) {
      return this;
   }
   else {
      if (this->nextState == NULL)
         std::cout << "something wrong\n";
      elapsedTime = 0;
      return this->nextState;
   }

}

MoveToState::MoveToState(NPC *bind, State *nextState, glm::vec3 MoveTo, float spd)
{
   toMove = bind;
   dest = MoveTo;
   this->nextState = nextState;
   speed = spd;
   
}

State* MoveToState::update(float dt)
{
   glm::vec3 dir = dest - toMove->getWorldPos() ;
   dir = glm::normalize(dir);
   dir = dir * speed;
   toMove->setVelocity(dir);


   if (glm::distance(toMove->getWorldPos(), dest) < 5)
   {
      if (this->nextState == NULL)
         std::cout << "something wrong\n";
      return this->nextState;
   }

   return this;
}

