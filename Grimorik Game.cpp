// Grimorik Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SDL.h"

void gameLoop(SDL_Renderer *renderer, SDL_Window *win)
{
   int cameraX = 0;
   int cameraY = 0;

   SDL_Surface *screen, *temp, *sprite;
   SDL_Texture *bitmapTex = NULL;
   SDL_Rect fillRect;


   temp = SDL_LoadBMP("materials/test/noct.bmp");
   bitmapTex = SDL_CreateTextureFromSurface(renderer, temp);
   SDL_FreeSurface(temp);

   float rectCoordX = 0, rectCoordY = 0;
   fillRect = { (int) rectCoordX, (int) rectCoordY, 240 / 2, 240 / 2 };

   Uint32 ticks;
   Uint32 seconds;
   float prev = 0, cur, dt = 0;


   while (1) {
      ticks = SDL_GetTicks();
      seconds = ticks / 1000;
      dt = ticks - prev;
      prev = ticks;

      SDL_Event e;
      if (SDL_PollEvent(&e)) {
         /* an event was found */
         switch (e.type) {
            /* close button clicked */
            case SDL_QUIT:
               return;
               break;
            /* handle the keyboard */
            case SDL_KEYDOWN:
               switch (e.key.keysym.sym) {
                  case SDLK_ESCAPE:
                  return;
                  break;
               }
               break;
         }

      }


      const Uint8* keystate = SDL_GetKeyboardState(NULL);

      //continuous-response keys
      if (keystate[SDL_SCANCODE_A])
      {
         rectCoordX -= .1 * dt;
         std::cout << fillRect.x << "\n";
      }
      if (keystate[SDL_SCANCODE_D])
      {
         rectCoordX += .1 * dt;
         std::cout << fillRect.x << "\n";
      }
      if (keystate[SDL_SCANCODE_W])
      {
         rectCoordY -= .1 * dt;
         std::cout << fillRect.y << "\n";
      }
      if (keystate[SDL_SCANCODE_S])
      {
         rectCoordY += .1 * dt;
         std::cout << fillRect.y << "\n";
      }

      fillRect.x = (int)rectCoordX;
      fillRect.y = (int)rectCoordY;


      // clears the screen
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderClear(renderer);

      // creates test rectangle to render to
      
      SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(renderer, &fillRect);
      
      SDL_RenderCopy(renderer, bitmapTex, NULL, &fillRect);



      SDL_RenderPresent(renderer);
   }
}



int main(int argc, char* argv[])
{
   SDL_Window *win = NULL;
   SDL_Renderer *renderer = NULL;
   int posX = 100, posY = 100, width = 800, height = 600;

   SDL_Init(SDL_INIT_VIDEO);

   win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

   renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

   gameLoop(renderer, win);   

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(win);

   SDL_Quit();

   return 0;
}