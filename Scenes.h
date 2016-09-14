#pragma once

#ifndef _SCENES_H_
#define _SCENES_H_

#include "SDL.h"
#include "GameObject.h"
#include "GameScene.h"
#include <vector>

#include "SDL_ttf.h"
#include <stdlib.h>
#include "DialogueBox.h"
#include "PlayerObject.h"
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
      PlayerObject *temp_player;
      GameObject *temp_player_static;
  
      WorldInfo *world_info;

   //   std::vector<GameObject *> objects;
      

      
  //    std::vector<int> objects;
};

class SceneInside : public GameScene
{
public:
   SceneInside();
   virtual ~SceneInside();
   virtual void setup(WorldInfo *world);
   virtual int processControl(float dt);
   virtual void update(float dt);
   virtual void render(float dt);

private:
   PlayerObject *temp_player;
   GameObject *temp_player_static;

   WorldInfo *world_info;

   //   std::vector<GameObject *> objects;



   //    std::vector<int> objects;
};

#endif