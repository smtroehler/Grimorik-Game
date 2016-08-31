#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "GameScene.h"
class SceneTown : public GameScene
{
   public:
      SceneTown();
      virtual void setup(WorldInfo *world);
      virtual int processControl(float dt);
      virtual void update(float dt);
      virtual void render(float dt);

   private:
      GameObject *temp_player;
      GameObject *temp_player_static;
      glm::vec2 playerVel = glm::vec2(0, 0);
      bool isMovingX = false, isMovingY = false;
};