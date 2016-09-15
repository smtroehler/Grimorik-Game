#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "SDL.h"
#include "GameUtilities.h"

#include "SDL_image.h"

//struct WorldInfo; 
//extern WorldInfo info;



class GameObject
{
   public:
      GameObject(int x, int y, int z, int w, int h, WorldInfo *info);
      virtual  ~GameObject();

      virtual void render();
      virtual void update(float dt);
      

      int getScreenX();
      int getScreenY();
      int getZ() { return worldZ; };
      float getWorldX();
      float getWorldY();
      int   getWidth() { return width; };
      int   getHeight() { return height; };
      float getVelX();
      float getVelY();
      float getVelZ();
      glm::vec3 getVelocity();
      glm::vec3 getWorldPos();

      void setImage(const char* file);
      void setColor(int r, int g, int b, int a);
      void setWorldPos(float x, float y);
     
      void setVelocity(float x, float y, float z);
      void setVelocity(glm::vec3 in);

      virtual void addToDrawList();
      virtual void removeFromDrawList();
      
      void setIsInteracting(bool in) { isInteracting = in; };

      bool isInteracting;

   protected:
      // Keeps track of world coords.
      float worldX, worldY, worldZ;
      float velX, velY, velZ;

      int width, height;
      int colorR, colorG, colorB, colorA;
      

      bool isParallaxed = false;

      WorldInfo *info_ptr;

      SDL_Texture *bitmapTex = NULL;
      SDL_Rect fillRect;
};

class CollideableObject : public GameObject
{
public:
   CollideableObject(int x, int y, int z, int w, int h, WorldInfo *info);
   BoundingBox *bbox;

   void setImage(const char* file);
   virtual void render();
   virtual void update(float dt);
   void setWorldPos(float x, float y);
   BoundingBox *getBBox() { return bbox; };

   virtual void addToDrawList();
   virtual void removeFromDrawList();

   void addToCollisionList();
   void removeFromCollisionList();

   void offSetBBox(float offsetx, float offsety, float w, float h);

   bool getIsSolid() { return isSolid; };
   void setIsSolid(bool in) { isSolid = in; };
   bool isSolid;
};

bool isFirstGameObject(GameObject *t, GameObject *o);
float distanceOfGO(GameObject *t, GameObject *o);
#endif