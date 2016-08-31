#include "GameObject.h"
#include "GameUtilities.h"
GameObject::GameObject(int x, int y, int z, int w, int h, WorldInfo *info)
{
   worldX = x;
   worldY = y;
   worldZ = z;

   colorR = 128;
   colorG = 128;
   colorB = 128;
   colorA = 255;

   width = w;
   height = h;

   info_ptr = info;
   fillRect = {x, y, w, h };
}

GameObject::~GameObject() {}

int GameObject::getScreenX()
{
   return  worldX - info_ptr->cameraPosX + info_ptr->screenWidth / 2 - width / 2;
}
int GameObject::getScreenY()
{
   return worldY - info_ptr->cameraPosY + info_ptr->screenHeight / 2 - height / 2;
}

void GameObject::setImage(const char* file)
{
   SDL_Surface *temp;
   temp = SDL_LoadBMP(file);
   bitmapTex = SDL_CreateTextureFromSurface(info_ptr->renderer, temp);
   SDL_FreeSurface(temp);
}

int GameObject::getWorldX()
{
   return worldX;
}

int GameObject::getWorldY()
{
   return worldY;
}

void GameObject::setWorldPos(int x, int y)
{
   worldX = x;
   worldY = y;
}


void GameObject::update(float dt) {}

void GameObject::render() {

   fillRect.x = worldX - info_ptr->cameraPosX + info_ptr->screenWidth / 2 - width / 2;
   fillRect.y = worldY - info_ptr->cameraPosY + info_ptr->screenHeight / 2 - height / 2;


   SDL_SetRenderDrawColor(info_ptr->renderer, colorR, colorG, colorB, colorA);
   SDL_RenderFillRect(info_ptr->renderer, &fillRect);

   if(bitmapTex != NULL)
      SDL_RenderCopy(info_ptr->renderer, bitmapTex, NULL, &fillRect);
}

