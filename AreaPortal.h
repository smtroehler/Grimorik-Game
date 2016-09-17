#pragma once
#include "GameObject.h"
#include "GameScene.h"
class Triggers : public CollideableObject
{
public:
   Triggers(int x, int y, int z, int w, int h, WorldInfo *info) :
      CollideableObject(x, y, z, w, h, info)
   {};
   virtual void render() = 0;
   virtual void update(float dt) = 0;

   virtual void addToDrawList() = 0;
   virtual void removeFromDrawList() = 0;

   void setNextScene(std::string toset, std::string enterAt) {
      nextScene = toset; entryPoint = enterAt; 
   };

   void reset() { timeExisting = 0; };

protected:
   std::string nextScene;
   std::string entryPoint;
   float timeExisting = 0;
   bool playerStartsInBox = false;
};

class AreaPortal : public Triggers
{
public:
   AreaPortal(int x, int y, int z, int w, int h, WorldInfo *info);
   virtual void render();
   virtual void update(float dt);

   virtual void addToDrawList();
   virtual void removeFromDrawList();

private:

   void transitionToScene();
};
