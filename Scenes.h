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
#include "AreaPortal.h"

class AreaTransition : public GameScene
{
public:
   AreaTransition(); 
   virtual void setup(WorldInfo *world);
   virtual int processControl(float dt);
   virtual void update(float dt);
   virtual void render(float dt);
   void setScenes(GameScene *from, GameScene *to);
   virtual void EnterScene(std::string in);
   void setFadeTime(float in1, float in2) {
      fadeOut = in1; fadeIn = in2; };
private:
   GameObject *blackOverlay;
   GameScene *from;
   GameScene *to;
   GameScene *cur;
   std::string entryPoint;
   float timeelapsed;
   float fadeOut, fadeIn;
};

class SceneTown : public GameScene
{
   public:
      SceneTown();
      virtual ~SceneTown();
      virtual void setup(WorldInfo *world);
      virtual int processControl(float dt);
      virtual void update(float dt);
      virtual void render(float dt);

      virtual void EnterScene(std::string entryPoint);
      virtual void exitingScene() { GameScene::exitingScene(); };
   private:
      PlayerObject *temp_player;
      GameObject *temp_player_static;
  
     
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

   virtual void EnterScene(std::string entryPoint);
   virtual void exitingScene() { GameScene::exitingScene(); };
private:

};

#endif