#pragma once

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SDL.h"
#include "GameUtilities.h"
#include <vector>
#include "GameObject.h"
#include "PlayerObject.h"
class GameScene
{
   public:
      GameScene() {};
      virtual void setup(WorldInfo *world) = 0;
      virtual int processControl(float dt) = 0;
      virtual void update(float dt) = 0;
      virtual void render(float dt) = 0;
      bool isSetup() { return setupCalled; };
      WorldInfo* getWorldInfoPtr() {return world_info;};
      virtual void EnterScene(std::string entryPoint) = 0;
      virtual void exitingScene() { 
         world_info->objects = &sceneObjects;
         world_info->collideables = &sceneCollideables;
         world_info->player->removeFromCollisionList();
         world_info->player->removeFromDrawList();
      };
      std::string getName() { return sceneName; };

      void resetPortals() {
         for (int i = 0; i < scenePortals.size(); i++)
            scenePortals.at(i)->reset(); }


protected:
   bool setupCalled = false;
   std::string sceneName; 
   WorldInfo *world_info;
   std::vector<GameObject *> sceneObjects;
   std::vector<CollideableObject *> sceneCollideables;
   std::vector<AreaPortal *> scenePortals;
};

#endif