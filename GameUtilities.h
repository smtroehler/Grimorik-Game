#pragma once

#ifndef _GAMEUTILITIES_H_
#define _GAMEUTILITIES_H_


#include "SDL.h"
#include "glm/glm.hpp"
#include <string>
#include "SDL_ttf.h"
#include <vector>
//#include "GameObject.h"


extern class CollideableObject;

struct BoundingBox {

   int x, y;
   int w, h;

};

struct WorldInfo
{
   int screenWidth;
   int screenHeight;
   int cameraPosX;
   int cameraPosY;
   int cameraPosZ;
   glm::vec3 cameraVelocity;
   glm::vec3 cameraAccel;
   float dt;
   SDL_Renderer *renderer;
   SDL_Window *win;
   TTF_Font* dialogueFont;
   const Uint8* keystates;

   std::vector<CollideableObject *> collideables;

};
#endif


// keep track of completed quests and quest items here
struct QuestTracker
{

};