#include "MenuItems.h"
#include <iostream>


MenuButton::MenuButton(int x, int y, int z, int w, int h, WorldInfo *info) :
   GameObject(x, y, z, w, h, info)
{
   pressed = false;
   pushed_down_rect = { x, y, w, h };
}

MenuButton::~MenuButton()
{
   GameObject::~GameObject();
   delete(pushed_down_tex);
}

void MenuButton::setPressFunction(void (*in)(WorldInfo *world_info))
{
   to_call = in;
}

void MenuButton::setPushedDownImage(const char* file)
{
   SDL_Surface *temp;
   temp = IMG_Load(file);

   glm::vec2 normedImage = normalizeImage(temp, width, height);
   pushed_down_rect = { (int)worldX,  (int)worldY,  (int)normedImage.x, (int)normedImage.y };
   pushed_down_tex = SDL_CreateTextureFromSurface(info_ptr->renderer, temp);

   SDL_FreeSurface(temp);
}

void MenuButton::render()
{
   fillRect.x = (int)(worldX - width / 2);
   fillRect.y = (int)(worldY - height / 2);

   SDL_SetRenderDrawBlendMode(info_ptr->renderer,
      SDL_BLENDMODE_BLEND);
   // draw it if it not being pressed or if the pressed image is not set
   if (!pressed || pushed_down_tex == NULL) {
      SDL_SetRenderDrawColor(info_ptr->renderer, colorR, colorG, colorB, colorA);
      SDL_RenderFillRect(info_ptr->renderer, &fillRect);

      if (bitmapTex != NULL) {
         SDL_RenderCopy(info_ptr->renderer, bitmapTex, NULL, &fillRect);

      }
   }

   // the pushed down image is completely optional so if it is not set don't draw anything
   if (pushed_down_tex != NULL && pressed) {
      pushed_down_rect.x = (int)(worldX - width / 2);
      pushed_down_rect.y = (int)(worldY - height / 2);

      SDL_SetRenderDrawColor(info_ptr->renderer, colorR, colorG, colorB, colorA);
      SDL_RenderFillRect(info_ptr->renderer, &pushed_down_rect);
      SDL_RenderCopy(info_ptr->renderer, pushed_down_tex, NULL, &pushed_down_rect);
   }
}
void MenuButton::update(float dt)
{
   

   int mouse_x, mouse_y;
   Uint32 state = SDL_GetMouseState(&mouse_x, &mouse_y);

   if (mouse_x > worldX - width / 2 && mouse_x < worldX + width / 2 &&
       mouse_y > worldY - height / 2 && mouse_y < worldY + height / 2)
   {
      if (state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
         pressed = true;
      } else if (pressed && !(state & SDL_BUTTON(SDL_BUTTON_LEFT))) {
         if (to_call != NULL) {
            to_call(info_ptr);
         }
      }
   }
   else
   {
      pressed = false;
   }
}

void MenuButton::addToDrawList()
{
   GameObject::addToDrawList();
}

void MenuButton::removeFromDrawList()
{
   GameObject::removeFromDrawList();
}


