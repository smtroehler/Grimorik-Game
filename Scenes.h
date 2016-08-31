#pragma once

#ifndef _SCENES_H_
#define _SCENES_H_

#include "SDL.h"
#include "GameObject.h"
#include "GameScene.h"
#include <vector>

#include <stdlib.h>
class SceneTown : public GameScene
{
   public:
      SceneTown();
      virtual ~SceneTown();
      virtual void setup(WorldInfo *world);
      virtual int processControl(float dt);
      virtual void update(float dt);
      virtual void render(float dt);

   private:
      GameObject *temp_player;
      GameObject *temp_player_static;
      glm::vec2 playerVel = glm::vec2(0, 0);
      bool isMovingX = false;
      bool isMovingY = false;
  
      WorldInfo *world_info;
      float rectCoordX = 0;
      float rectCoordY = 0;

      std::vector<GameObject *> objects;
  //    std::vector<int> objects;
};

#endif