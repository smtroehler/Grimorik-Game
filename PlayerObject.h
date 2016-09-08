#pragma once
#include "GameObject.h"

class PlayerObject : public CollideableObject
{
public:
   PlayerObject(int x, int y, int z, int w, int h, WorldInfo *info);

   virtual void render();
   virtual void update(float dt);
};