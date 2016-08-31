#pragma once

#include "SDL.h"
#include "GameUtilities.h"
class GameScene
{
   public:
      GameScene() {};
      virtual void setup(WorldInfo *world) = 0;
      virtual int processControl(float dt) = 0;
      virtual void update(float dt) = 0;
      virtual void render(float dt) = 0;

      WorldInfo *world_info;
};