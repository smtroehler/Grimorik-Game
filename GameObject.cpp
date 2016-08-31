#include "GameObject.h"
#include "GameUtilities.h"
#include "SDL_image.h"
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
   SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0xFF, 0, 0xFF));
   
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

void GameObject::setWorldPos(int x, int y)
{
   worldX = x;
   worldY = y;
}


void GameObject::update(float dt) {}

void GameObject::render() {

   fillRect.x = (int) worldX - info_ptr->cameraPosX + info_ptr->screenWidth / 2 - width / 2;
   fillRect.y = (int) worldY - info_ptr->cameraPosY + info_ptr->screenHeight / 2 - height / 2;


   

   SDL_SetRenderDrawColor(info_ptr->renderer, colorR, colorG, colorB, colorA);
   SDL_RenderFillRect(info_ptr->renderer, &fillRect);

   if(bitmapTex != NULL)
      SDL_RenderCopy(info_ptr->renderer, bitmapTex, NULL, &fillRect);
}

