#pragma once
#include "GameObject.h"

class State
{
public:
   State();

   virtual State update(float dt);
};

class NPC : public GameObject
{
   public:
      NPC(int x, int y, int z, int w, int h, WorldInfo *info);
      

      virtual void render();
      virtual void update(float dt);

      GameObject *has_quest_symbol;

   private:

      bool hasQuest = true; 
      bool canFight = false;
};


