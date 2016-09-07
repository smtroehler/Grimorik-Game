#pragma once

#ifndef _DIALOGUEBOX_H_
#define _DIALOGUEBOX_H_


#include "glm/glm.hpp"
#include "GameUtilities.h"

#include "SDL.h"
#include "SDL_image.h"
#include <string>


class DialogueBox
{
   public:
      DialogueBox(WorldInfo *info, glm::vec3 pos, std::string t);
      void setPosition(glm::vec3 in);
      void setText(std::string in);
      void setTextColor(glm::vec3 in);
      void setTextColor(int r, int g,int b);
      void setTalkingSprite(std::string filename);
      void render();
   private:
      std::string text;
      WorldInfo *info;
      SDL_Color fontColor;
      SDL_Texture *talkingSprite = NULL;
      SDL_Rect talkingSpriteRect;
      glm::vec2 talkingSpriteSize;

      SDL_Texture *textBoxSprite = NULL;
      SDL_Rect textBoxRect;

      SDL_Texture *textTexture = NULL;
      SDL_Rect textRect;
      SDL_Surface* textSurface;

      SDL_Rect screenCoverRect;
};

#endif