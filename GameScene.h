#pragma once

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SDL.h"
#include "GameUtilities.h"
#include <vector>
#include "GameObject.h"

class GameScene
{
   public:
      GameScene() {};
      virtual void setup(WorldInfo *world) = 0;
      virtual int processControl(float dt) = 0;
      virtual void update(float dt) = 0;
      virtual void render(float dt) = 0;

   
};

#endif