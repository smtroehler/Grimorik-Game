#include "Scenes.h"
#include <iostream>
#include <algorithm>    // std::sort
void startGame(WorldInfo *world_info);
MainMenu::MainMenu() {
}

MainMenu::~MainMenu()
{
   std::cout << "deleting menu\n";
   sceneObjects.clear();
}

void MainMenu::setup(WorldInfo *world) {
   world_info = world;

   // we want to clear all game scenes
   world_info->scenes = std::vector<GameScene *>();

   sceneObjects = std::vector<GameObject *>();
   sceneCollideables = std::vector<CollideableObject *>();

   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;
   
   MenuButton *ptr = new MenuButton(world_info->screenWidth / 2, world_info->screenHeight / 7, 0, 
      300, world_info->screenHeight / 7, world);
   ptr->setImage("materials/test/start_button_up.png");
   ptr->setPressFunction(&startGame);
   ptr->addToDrawList();
   buttons.push_back(ptr);


   ptr->setPushedDownImage("materials/test/start_button_down.png");
}
int MainMenu::processControl(float dt) {

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
   return 0;
}

void MainMenu::update(float dt) {
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;
   for (int i = 0;  i < world_info->objects->size();i++)
   {
      world_info->objects->at(i)->update(dt);
   }

   std::sort(world_info->objects->begin(), world_info->objects->end(), isFirstGameObject);
}

void MainMenu::render(float dt) {
   world_info->objects = &sceneObjects;
   world_info->collideables = &sceneCollideables;
   for (int i = 0; i < world_info->objects->size();i++)
   {

      world_info->objects->at(i)->render();
   }
}

void MainMenu::EnterScene(std::string entryPoint) {

}

void startGame(WorldInfo *world_info)
{
 //  delete(world_info->curScene);
   world_info->scenes.clear();
   
   GameScene *scene1 = new SceneTown();
   scene1->setup(world_info);
   world_info->curScene = scene1;
   world_info->scenes.push_back(scene1);

   // create the cave scene
   scene1 = new SceneInside();
   scene1->setup(world_info);
   world_info->scenes.push_back(scene1);
   
}