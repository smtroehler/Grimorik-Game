#include "DialogueBox.h"
#include "SDL_ttf.h"
#include <iostream>

#include "GameUtilities.h"

std::string dialogueFont = "materials/fonts/KELMSCOT.ttf";
DialogueBox::DialogueBox(WorldInfo *worldinfo, glm::vec3 pos, std::string t) {
   info = worldinfo;
   text = t;

   TTF_Font* Sans = TTF_OpenFont(dialogueFont.c_str(), 24);
   fontColor = { 255, 255, 255 }; 
   textSurface = TTF_RenderText_Solid(Sans, text.c_str(), fontColor);
   textTexture = SDL_CreateTextureFromSurface(info->renderer, textSurface);

   talkingSpriteRect = { 0,0,0,0 };

   SDL_Surface *temp;
   temp = IMG_Load("materials/interaction/dialoguebg.png");
   textBoxSprite = SDL_CreateTextureFromSurface(info->renderer, temp);
   textBoxRect = { 0,0,0,0 };


   SDL_FreeSurface(temp);
}

void DialogueBox::setPosition(glm::vec3 in)
{

}

void DialogueBox::setTextColor(glm::vec3 in)
{
   fontColor = { (Uint8) in.x, (Uint8) in.y, (Uint8) in.z};
   TTF_Font* Sans = TTF_OpenFont(dialogueFont.c_str(), 24);
   textSurface = TTF_RenderText_Solid(Sans, text.c_str(), fontColor);
   textTexture = SDL_CreateTextureFromSurface(info->renderer, textSurface);
}

void DialogueBox::setText(std::string in)
{
   text = in;
   TTF_Font* Sans = TTF_OpenFont(dialogueFont.c_str(), 24);
   textSurface = TTF_RenderText_Solid(Sans, text.c_str(), fontColor);
   textTexture = SDL_CreateTextureFromSurface(info->renderer, textSurface);
}

void DialogueBox::setTextColor(int r, int g, int b)
{
   fontColor = { (Uint8) r,(Uint8) g, (Uint8) b};
   TTF_Font* Sans = TTF_OpenFont(dialogueFont.c_str(), 24);
   textSurface = TTF_RenderText_Solid(Sans, text.c_str(), fontColor);
   textTexture = SDL_CreateTextureFromSurface(info->renderer, textSurface);
}

void DialogueBox::setTalkingSprite(std::string filename)
{
   SDL_Surface *temp;
   temp = IMG_Load(filename.c_str());
   talkingSpriteSize = glm::vec2(temp->w, temp->h);

   float scale = talkingSpriteSize.x / (info->screenWidth / 3.0f);
   talkingSpriteSize.x = info->screenWidth / 3.0f;
   talkingSpriteSize.y = talkingSpriteSize.y / scale;
    

   talkingSprite = SDL_CreateTextureFromSurface(info->renderer, temp);
   SDL_FreeSurface(temp);
}

void DialogueBox::render()
{
   textBoxRect.w = info->screenWidth / 5 * 4;
   textBoxRect.h = info->screenHeight / 4 ;
   textBoxRect.x = info->screenWidth / 2 - textBoxRect.w / 2;
   textBoxRect.y = info->screenHeight / 4 * 3 - 20 ;
   
   SDL_RenderCopy(info->renderer, textBoxSprite, NULL, &textBoxRect);

   // draw the talking character
   if (talkingSprite != NULL) {
      talkingSpriteRect.x = info->screenWidth / 5 * 4 - talkingSpriteSize.x / 2;
      talkingSpriteRect.y = info->screenHeight / 3 * 2;
      talkingSpriteRect.w = talkingSpriteSize.x;
      talkingSpriteRect.h = talkingSpriteSize.y;

      SDL_SetRenderDrawBlendMode(info->renderer,
         SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(info->renderer, 0, 0, 0, 0);
      SDL_RenderFillRect(info->renderer, &talkingSpriteRect);
      SDL_RenderCopy(info->renderer, talkingSprite, NULL, &talkingSpriteRect);
   }

  
   // set the position and draw the text
   SDL_Rect Message_rect; //create a rect
   Message_rect.x = info->screenWidth / 4;  //controls the rect's x coordinate 
   Message_rect.y = info->screenHeight / 4 * 3; // controls the rect's y coordinte
   Message_rect.w = textSurface->w; // controls the width of the rect
   Message_rect.h = textSurface->h; // controls the height of the rect
   
   SDL_RenderCopy(info->renderer, textTexture, NULL, &Message_rect);
}