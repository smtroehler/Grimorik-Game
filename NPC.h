#pragma once
#include "GameObject.h"
#include <vector>
class State
{
public:
   State() {};

   virtual State *update(float dt) = 0;
   virtual void setNextState(State *toSet) = 0;
};

class NPC : public CollideableObject
{
   public:
      NPC(int x, int y, int z, int w, int h, WorldInfo *info);
      

      virtual void render();
      virtual void update(float dt);
      virtual void interact();
      virtual void interactionFinished();
      virtual void setStates(std::vector <State *> in);
      GameObject *has_quest_symbol;

      std::string getName() { return name; };
      void setName(std::string in) { name = in; };

   protected:
      glm::vec3 prevVelocity;
      bool isInteractionFinished = true;
      bool hasQuest = true; 
      bool canFight = false;
      State *curState;
      std::vector<State *> states;
      std::string name;

      SDL_Texture *talkingSprite = NULL;
   private:
     
};

std::vector<NPC*> NPCLoader(std::string in, WorldInfo *world_info);

class NPCTEST : public NPC
{
public:
   NPCTEST(int x, int y, int z, int w, int h, WorldInfo *info);


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

