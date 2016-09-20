#pragma once
#include "GameObject.h"

class MenuButton : public GameObject
{
public:
   MenuButton(int x, int y, int z, int w, int h, WorldInfo *info);
   ~MenuButton();

   virtual void render();
   virtual void update(float dt);
   virtual void addToDrawList();
   virtual void removeFromDrawList();
   void setPushedDownImage(const char* file);
   void setPressFunction(void(*in)(WorldInfo *world_info));
private:
   void(*to_call)(WorldInfo *world_info);
   bool pressed;

   SDL_Texture *pushed_down_tex = NULL;
   SDL_Rect pushed_down_rect;
};

