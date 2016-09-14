#pragma once
#include "GameObject.h"
#include "GameScene.h"
class AreaPortal : public CollideableObject
{

   AreaPortal(int x, int y, int z, int w, int h, WorldInfo *info);
   virtual void render();
   virtual void update(float dt);

   virtual void addToDrawList();
   virtual void removeFromDrawList();

private:
   GameScene *nextScene;
   float timeExisting = 0;
};
