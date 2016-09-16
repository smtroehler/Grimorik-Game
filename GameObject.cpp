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

   isInteracting = false;
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

glm::vec2 normalizeImage(SDL_Surface *temp, int width , int height)
{
   float imgw, imgh, biggest, db1, scale;

   db1 = width;
   if (height > db1)
      db1 = height;

   imgw = temp->w;
   imgh = temp->h;
   if (imgh > imgw) {
      scale = imgh / db1;
   }
   else
   {
      scale = imgw / db1;
   }
   width = imgw / scale;
   height = imgh / scale;
   return glm::vec2(width, height);
}

void GameObject::setImage(const char* file)
{
   SDL_Surface *temp;
   temp = IMG_Load(file);

   glm::vec2 normedImage = normalizeImage(temp, width, height);
   width = (int)normedImage.x;
   height = (int)normedImage.y;
   fillRect = { (int)worldX,  (int)worldY,  (int)normedImage.x, (int)normedImage.y };
   bitmapTex = SDL_CreateTextureFromSurface(info_ptr->renderer, temp);

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

void GameObject::setColor(int r, int g, int b, int a)
{
   colorR = r;
   colorG = g;
   colorB = b;
   colorA = a;
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

   fillRect.x = (int) (worldX - info_ptr->cameraPosX + info_ptr->screenWidth / 2 - width / 2);
   fillRect.y = (int) (worldY - info_ptr->cameraPosY + info_ptr->screenHeight / 2 - height / 2);


   
   SDL_SetRenderDrawBlendMode(info_ptr->renderer,
      SDL_BLENDMODE_BLEND);

   SDL_SetRenderDrawColor(info_ptr->renderer, colorR, colorG, colorB, colorA);
   SDL_RenderFillRect(info_ptr->renderer, &fillRect);

   if(bitmapTex != NULL)
      SDL_RenderCopy(info_ptr->renderer, bitmapTex, NULL, &fillRect);
}

void GameObject::addToDrawList()
{
   bool notInList = true;
   for (int i = 0; i < info_ptr->objects->size(); i++)
   {
      if (this == info_ptr->objects->at(i))
      {
         notInList = false;
      }
   }

   if (notInList)
   {
      info_ptr->objects->push_back(this);
   }
   
}

void GameObject::removeFromDrawList()
{
   for (int i = 0; i < info_ptr->objects->size(); i++)
   {
      if (info_ptr->objects->at(i) == this)
      {
         info_ptr->objects->erase(info_ptr->objects->begin() + i);
      }
   }
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

CollideableObject::CollideableObject(int x, int y, int z, int w, int h, WorldInfo *info) : 
   GameObject(x, y, z, w, h, info)
{

   bbox = new BoundingBox();
   bbox->x = x;
   bbox->y = y;
   bbox->w = w;
   bbox->h = h;
   bbox->offsetx = 0;
   bbox->offsety = 0;
   isSolid = true;
}

void CollideableObject::render()
{
   GameObject::render();
}

#include "PlayerObject.h"
void CollideableObject::update(float dt)
{
   bbox->x = worldX;
   bbox->y = worldY;

   for (int i = 0; i < info_ptr->collideables->size(); i++)
   {
      if (info_ptr->collideables->at(i) != this && info_ptr->collideables->at(i)->getIsSolid())
      {
         
         BoundingBox *bbox2 = info_ptr->collideables->at(i)->getBBox();
         float d1x = (bbox2->x + bbox2->offsetx - bbox2->w / 2) - (bbox->x + bbox->offsetx + bbox->w / 2);
         float d1y = (bbox2->y + bbox2->offsety - bbox2->h / 2) - (bbox->y + bbox->offsety + bbox->h / 2);
         float d2x = (bbox->x + bbox->offsetx - bbox->w / 2) - (bbox2->x + bbox2->offsetx + bbox2->w / 2);
         float d2y = (bbox->y + bbox->offsety - bbox->h / 2) - (bbox2->y + bbox2->offsety + bbox2->h / 2);

         if (d1x > 0.0f || d1y > 0.0f)
         {
          
         }
         else if (d2x > 0.0f || d2y > 0.0f)
         {
         }
         else
         {
            if (d2x > -3 && velX < 0)
               velX = 0;
            if (d1x  > -3 && velX > 0)
               velX = 0;
            if (d2y > -3 && velY < 0)
            {
               velY = 0;
            }
            if (d1y > -3 && velY > 0)
            {
               velY = 0;
            }
            
         }
      }
   }

   GameObject::update(dt);

   bbox->x = worldX;
   bbox->y = worldY;
}
void CollideableObject::setWorldPos(float x, float y)
{
   GameObject::setWorldPos(x, y);
   bbox->x = x;
   bbox->y = y;
}

void CollideableObject::setImage(const char* file)
{
   GameObject::setImage(file);
   bbox->offsetx = 0;
   bbox->offsetx = 0;
   bbox->x = worldX;
   bbox->y = worldY;
   bbox->w = width;
   bbox->h = height;
}

void CollideableObject::addToDrawList()
{
   GameObject::addToDrawList();
}

void CollideableObject::removeFromDrawList()
{
   GameObject::removeFromDrawList();
}

void CollideableObject::offSetBBox(float offsetx, float offsety, float w, float h)
{
   if (offsetx != -1)
      bbox->offsetx = offsetx;
   if (offsety != -1)
      bbox->offsety = offsety;
   if (w != -1)
      bbox->w = w;
   if (h != -1)
      bbox->h = h;
}

void CollideableObject::addToCollisionList()
{
   bool notInList = true;
   for (int i = 0; i < info_ptr->collideables->size(); i++)
   {
      if (this == info_ptr->collideables->at(i))
      {
         notInList = false;
      }
   }

   if (notInList)
   {
      info_ptr->collideables->push_back(this);
   }

}

void CollideableObject::removeFromCollisionList()
{
   for (int i = 0; i < info_ptr->collideables->size(); i++)
   {
      if (info_ptr->collideables->at(i) == this)
      {
         info_ptr->collideables->erase(info_ptr->collideables->begin() + i);
      }
   }
}