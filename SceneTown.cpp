#include "Scenes.h"
#include  <vector>
SceneTown::SceneTown()
{

}

SceneTown::~SceneTown()
{

}


void SceneTown::setup(WorldInfo *world)
{
   world_info = world;
   temp_player = new GameObject(0, 0, 0, 80, 80, world_info);
   temp_player->setImage("materials/test/noct.png");

   temp_player_static = new GameObject(0, 0, 0, 120, 120, world_info);
   temp_player_static->setImage("materials/test/noct.png");

   

   GameObject *temp_bg = new GameObject(0, 0, 0, 1024 , 1024, world_info);
   temp_bg->setImage("materials/test/bg.png");
   objects = std::vector<GameObject *>();
   objects.push_back(temp_bg);
}

int SceneTown::processControl(float dt)
{
   SDL_Event e;
   if (SDL_PollEvent(&e)) {
      /* an event was found */
      switch (e.type) {
         /* close button clicked */
      case SDL_QUIT:
         return -1;
         break;
         /* handle the keyboard */
      case SDL_KEYDOWN:
         switch (e.key.keysym.sym) {
         case SDLK_ESCAPE:
            return -1;
            break;
         }
         break;
      }

   }

   const Uint8* keystate = SDL_GetKeyboardState(NULL);

   isMovingX = false;
   isMovingY = false;

   //continuous-response keys SEND INPUT TO PLAYER CLASS TO HANDLE MOVEMENT
   if (keystate[SDL_SCANCODE_A])
   {
      playerVel.x = -300;
      isMovingX = true;
   }
   if (keystate[SDL_SCANCODE_D])
   {
      playerVel.x = 300;
      isMovingX = true;
   }
   if (keystate[SDL_SCANCODE_W])
   {
      playerVel.y = -300;
      isMovingY = true;
   }
   if (keystate[SDL_SCANCODE_S])
   {
      playerVel.y = 300;
      isMovingY = true;
   }
   return 1;
}

void SceneTown::update(float dt)
{
   if (isMovingX == false)
   {
      playerVel.x += 15 * -playerVel.x * dt;
   }

   if (isMovingY == false)
   {
      playerVel.y += 15 * -playerVel.y * dt;
   }
   rectCoordX += playerVel.x * dt;
   rectCoordY += playerVel.y * dt;

   temp_player->setWorldPos((int)rectCoordX, (int)rectCoordY);

   glm::vec2 dif = glm::vec2(rectCoordX - world_info->cameraPosX, rectCoordY - world_info->cameraPosY);

   world_info->cameraPosX = (int)rectCoordX;
   world_info->cameraPosY = (int)rectCoordY;
}

void SceneTown::render(float dt)
{
   

   

  
   for (int i = 0; i < objects.size(); i++)
   {
      objects.at(i)->render();
   }
   temp_player->render();
   temp_player_static->render();
   
   SDL_RenderPresent(world_info->renderer);
}