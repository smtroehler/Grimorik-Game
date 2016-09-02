#pragma once
#include "GameObject.h"

class State
{
public:
   State() {};

   virtual State *update(float dt) = 0;
   virtual void setNextState(State *toSet) = 0;
};

class NPC : public GameObject
{
   public:
      NPC(int x, int y, int z, int w, int h, WorldInfo *info);
      

      virtual void render();
      virtual void update(float dt);
      virtual void interact();
      virtual void interactionFinished();
      GameObject *has_quest_symbol;

   protected:
      glm::vec3 prevVelocity;
      bool isInteractionFinished = true;
      bool hasQuest = true; 
      bool canFight = false;
      State *curState;
   private:
     
};

