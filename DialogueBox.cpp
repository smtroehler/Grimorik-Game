#include "DialogueBox.h"
#include "SDL_ttf.h"
#include <iostream>

#include "GameUtilities.h"

std::string dialogueFont = "materials/fonts/KELMSCOT.ttf";



DialogueBox::DialogueBox(WorldInfo *worldinfo, glm::vec3 pos, std::string t) : GameObject(0,0,0,0,0,worldinfo) {
   info = worldinfo;
   textlines.push_back(t);

   font = TTF_OpenFont(dialogueFont.c_str(), 24);
   fontColor = { 255, 255, 255 }; 
   textSurface.push_back(TTF_RenderText_Solid(font, textlines.at(0).c_str(), fontColor));
   textTexture.push_back(SDL_CreateTextureFromSurface(info->renderer, textSurface.at(0)));

   talkingSpriteRect = { 0,0,0,0 };

   SDL_Surface *temp;
   temp = IMG_Load("materials/interaction/dialoguebg.png");
   textBoxSprite = SDL_CreateTextureFromSurface(info->renderer, temp);
   textBoxRect = { 0,0,0,0 };
   SDL_FreeSurface(temp);

   alignedRight = true;
}

void DialogueBox::setPosition(glm::vec3 in)
{

}

void DialogueBox::setTextColor(glm::vec3 in)
{
   fontColor = { (Uint8) in.x, (Uint8) in.y, (Uint8) in.z};
}

void DialogueBox::setText(std::string in, int i)
{
   if (i >= textlines.size())
      return;

   textlines.at(i) = in;
   textSurface.at(i) = TTF_RenderText_Solid(font, textlines.at(i).c_str(), fontColor);
   textTexture.at(i) = (SDL_CreateTextureFromSurface(info->renderer, textSurface.at(i)));
}

void DialogueBox::setTextColor(int r, int g, int b)
{
   fontColor = { (Uint8) r,(Uint8) g, (Uint8) b};
}

void DialogueBox::addLineOfText(std::string in)
{
   textlines.push_back(in);
   textSurface.push_back(TTF_RenderText_Solid(font, textlines.at(textlines.size()-1).c_str(), fontColor));
   textTexture.push_back(SDL_CreateTextureFromSurface(info->renderer, textSurface.at(textlines.size() - 1)));
}

void DialogueBox::setTalkingSprite(std::string filename)
{
   SDL_Surface *temp;
   temp = IMG_Load(filename.c_str());
   talkingSpriteSize = glm::vec2(temp->w, temp->h);

   float scale = talkingSpriteSize.x / (info->screenWidth / 6.0f);
   talkingSpriteSize.x = info->screenWidth / 6.0f;
   talkingSpriteSize.y = talkingSpriteSize.y / scale;
    

   talkingSprite = SDL_CreateTextureFromSurface(info->renderer, temp);
   SDL_FreeSurface(temp);
}

void DialogueBox::alignRight()
{
   alignedRight = true;
}
void DialogueBox::alignLeft()
{
   alignedRight = false;
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
      if (alignedRight == true) {
         talkingSpriteRect.x = info->screenWidth / 7 * 6 - talkingSpriteSize.x / 2;
      } else {
         talkingSpriteRect.x = info->screenWidth / 8 - talkingSpriteSize.x / 2;
      }

      talkingSpriteRect.y = info->screenHeight / 3 * 2;
      talkingSpriteRect.w = talkingSpriteSize.x;
      talkingSpriteRect.h = talkingSpriteSize.y;

      SDL_SetRenderDrawBlendMode(info->renderer,
         SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(info->renderer, 0, 0, 0, 0);
      SDL_RenderFillRect(info->renderer, &talkingSpriteRect);
      SDL_RenderCopy(info->renderer, talkingSprite, NULL, &talkingSpriteRect);
   }

   for (int i = 0; i < textlines.size(); i++) {

      SDL_Rect Message_rect; //create a rect
      Message_rect.x = info->screenWidth / 4;  //controls the rect's x coordinate 
      Message_rect.y = info->screenHeight / 4 * 3 + i*30; // controls the rect's y coordinte
      Message_rect.w = this->textSurface.at(i)->w; // controls the width of the rect
      Message_rect.h = this->textSurface.at(i)->h; // controls the height of the rect
   
      SDL_RenderCopy(info->renderer, textTexture.at(i), NULL, &Message_rect);
   }
}

DialogueScene::DialogueScene(WorldInfo *world)
{
   info = world;
}

void DialogueScene::addDialogueBox(DialogueBox *toAdd)
{
   boxes.push_back(toAdd);
}

void DialogueScene::addResponseBox(DialogueBox *toAdd)
{
   boxes.push_back(toAdd);
}

bool DialogueScene::dialogueIsFinished()
{
   if (curBox >= boxes.size())
      return true;
   return false;
}


int DialogueScene::update(float dt)
{
   timer += dt;

   if (info->keystates[SDL_SCANCODE_E])
   {
      if (timer > 1)
      {
         curBox++;
         if (curBox >= boxes.size())
            return -1;
         timer = 0;
      }
   }
}

// returns the box that needs to be currently rendered
DialogueBox *DialogueScene::toRender()
{
   if (curBox >= boxes.size())
      return NULL;

   return boxes.at(curBox);
}