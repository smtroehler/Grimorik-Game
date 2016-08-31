#pragma once

#include "SDL.h"
#include "GameUtilities.h"

class GameObject
{
   public:
      GameObject(int x, int y, int z, int w, int h, WorldInfo *info);
      virtual  ~GameObject();

      virtual void render();
      virtual void update(float dt);
      

      int getScreenX();
      int getScreenY();
      int getZ();
      float getWorldX();
      float getWorldY();
      int   getWidth();
      int   getHeight();

      void setImage(const char* file);
      void setColor(int r, int g, int b, int a);
      void setWorldPos(int x, int y);
     
   private:
      // Keeps track of world coords.
      float worldX, worldY, worldZ;
      int width, height;
      int colorR, colorG, colorB, colorA;
      BoundingBox bbox;

      bool isParallaxed = false;

      WorldInfo *info_ptr;

      SDL_Texture *bitmapTex = NULL;
      SDL_Rect fillRect;
};
