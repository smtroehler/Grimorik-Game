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

CollideableObject::CollideableObject(int x, int y, int z, int w, int h, WorldInfo *info) : 
   GameObject(x, y, z, w, h, info)
{

   bbox = new BoundingBox();
   bbox->x = x;
   bbox->y = y;
   bbox->w = h;
   bbox->w = h;
}

void CollideableObject::render()
{
   GameObject::render();
}
void CollideableObject::update(float dt)
{
   bbox->x = worldX;
   bbox->y = worldY;

   for (int i = 0; i < info_ptr->collideables.size(); i++)
   {
      if (info_ptr->collideables.at(i) != this)
      {
        
         BoundingBox *bbox2 = info_ptr->collideables.at(i)->getBBox();
         float d1x = bbox2->x - bbox->x - bbox->w / 2;
         float d1y = bbox2->y - bbox->y - bbox->h ;
         float d2x = bbox->x - bbox2->x - bbox2->w / 2;
         float d2y = bbox->y - bbox2->y - bbox2->h ;

         float smallest = d1x;

      //   std::cout << d1x << " " << d1x << " " << d2x << " " << d2y << "\n";
         if (d1x > 0.0f || d1y > 0.0f)
         {

         }
         else if (d2x > 0.0f || d2y > 0.0f)
         {

         }
         else
         {
            if(d1x > d2x)
            std::cout << "collision\n";
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
   bbox->x = worldX;
   bbox->y = worldY;
   bbox->w = width;
   bbox->h = height;
}