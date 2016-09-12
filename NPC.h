#pragma once
#include "GameObject.h"
#include <vector>
#include "DialogueBox.h"
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
      void setDialogueScene(DialogueScene *in) { curScene = in; };

      std::string getName() { return name; };
      void setName(std::string in) { name = in; };

   protected:
      bool isInteractionFinished = true;
      bool hasQuest = true; 
      bool canFight = false;
      bool interactionBegun = false;

      State *curState;

      std::vector<State *> states;
      std::string name;

      float last_spoken_to;

      SDL_Texture *talkingSprite = NULL;

      GameObject *has_quest_symbol;

      DialogueScene *curScene;
   private:
     
};

std::vector<NPC*> NPCLoader(std::string in, WorldInfo *world_info);



