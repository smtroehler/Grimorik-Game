#include "GameObject.h"
#include "GameUtilities.h"
#include "SDL_image.h"
#include <iostream>
GameObject::GameObject(int x, int y, int z, int w, int h, WorldInfo *info)
{
   worldX = x;
   worldY = y;
   worldZ = z;

   velX = 0;
   velY = 0;
   velZ = 0;

   colorR = 128;
   colorG = 128;
   colorB = 128;
   colorA = 0;

   width = w;
   height = h;

   info_ptr = info;
   fillRect = {x, y, w, h };
}

GameObject::~GameObject() {}

int GameObject::getScreenX()
{
   return  (int) worldX - info_ptr->cameraPosX + info_ptr->screenWidth / 2 ;
}
int GameObject::getScreenY()
{
   return (int) worldY - info_ptr->cameraPosY + info_ptr->screenHeight / 2 ;
}

void GameObject::setImage(const char* file)
{
   SDL_Surface *temp;
   temp = IMG_Load(file);
  // SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0xFF, 0, 0xFF));
   
   bitmapTex = SDL_CreateTextureFromSurface(info_ptr->renderer, temp);
  // temp->setBlendMode(SDL_BLENDMODE_BLEND);

   SDL_FreeSurface(temp);

  
}

float GameObject::getWorldX()
{
   return worldX;
}

float GameObject::getWorldY()
{
   return worldY;
}

void GameObject::setWorldPos(float x, float y)
{
   worldX = x;
   worldY = y;
}

void GameObject::setVelocity(float x, float y, float z)
{
   velX = x;
   velY = y;
   velZ = z;
}

void GameObject::setVelocity(glm::vec3 in)
{
   velX = in.x;
   velY = in.y;
   velZ = in.z;
}

float GameObject::getVelX()
{
   return velX;
}
float GameObject::getVelY()
{
   return velY;
}
float GameObject::getVelZ()
{
   return velZ;
}

glm::vec3 GameObject::getVelocity()
{
   return glm::vec3(velX, velY, velZ);
}

glm::vec3 GameObject::getWorldPos()
{
   return glm::vec3(worldX, worldY, worldZ);
}

void GameObject::update(float dt) {

   worldX += velX * dt;
   worldY += velY * dt;
   worldZ += velZ * dt;

}

void GameObject::render() {

   fillRect.x = (int) worldX - info_ptr->cameraPosX + info_ptr->screenWidth / 2 - width / 2;
   fillRect.y = (int) (worldY - info_ptr->cameraPosY + info_ptr->screenHeight / 2 - height / 2);


   
   SDL_SetRenderDrawBlendMode(info_ptr->renderer,
      SDL_BLENDMODE_BLEND);

   SDL_SetRenderDrawColor(info_ptr->renderer, colorR, colorG, colorB, colorA);
   SDL_RenderFillRect(info_ptr->renderer, &fillRect);

   if(bitmapTex != NULL)
      SDL_RenderCopy(info_ptr->renderer, bitmapTex, NULL, &fillRect);
}

bool isFirstGameObject(GameObject *t, GameObject *o)
{
   if (t->getZ() > o->getZ())
      return false;
   if (t->getWorldY() + (t->getHeight() / 2.0f) > o->getWorldY() + (o->getHeight() / 2))
      return false;
   return true;
}

float distanceOfGO(GameObject *t, GameObject *o)
{
   glm::vec3 diff = o->getWorldPos() - t->getWorldPos();
   return std::abs(glm::length(diff));
}