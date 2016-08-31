#pragma once

#include "SDL.h"
#include "glm/glm.hpp"
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
};
