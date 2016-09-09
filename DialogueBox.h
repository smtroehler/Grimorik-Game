#pragma once

#ifndef _DIALOGUEBOX_H_
#define _DIALOGUEBOX_H_


#include "glm/glm.hpp"
#include "GameUtilities.h"
#include "GameObject.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>


extern WorldInfo;
class DialogueBox : public GameObject
{
   public:
      DialogueBox(WorldInfo *info, glm::vec3 pos, std::string t);
      void setPosition(glm::vec3 in);
      void setText(std::string in, int i);
      void setTextColor(glm::vec3 in);
      void setTextColor(int r, int g,int b);
      void setTalkingSprite(std::string filename);
      void addLineOfText(std::string in);
      virtual void render();
      void alignRight();
      void alignLeft();

      virtual void addToDrawList();
      virtual void removeFromDrawList();

   private:
      bool alignedRight;

      std::vector<std::string> textlines;
      WorldInfo *info;
      SDL_Color fontColor;

      TTF_Font* font;

      SDL_Texture *talkingSprite = NULL;
      SDL_Rect talkingSpriteRect;
      glm::vec2 talkingSpriteSize;

      SDL_Texture *textBoxSprite = NULL;
      SDL_Rect textBoxRect;

      std::vector<SDL_Texture *> textTexture;
      SDL_Rect textRect;
      std::vector<SDL_Surface*> textSurface;

      SDL_Rect screenCoverRect;
};

class DialogueScene
{
public:
   DialogueScene(WorldInfo *world);
   void addDialogueBox(DialogueBox *toAdd);
   void addResponseBox(DialogueBox *toAdd);
   // If there is no next scene set then return itself so this dialog will repeat
   DialogueScene *getNextScene() { if (nextScene) return nextScene; else return this; };
   void setNextScene(DialogueScene *in) { nextScene = in; };
   bool dialogueIsFinished();
   int update(float dt);
   
   // returns the box that needs to be currently rendered
   DialogueBox *toRender();
   void start();
private:
   int curBox = 0;
   WorldInfo *info;
   std::vector<DialogueBox *> boxes;
   DialogueScene *nextScene;
   float timer;
};

class DialogueBoxResponse : public DialogueBox
{

};


#endif