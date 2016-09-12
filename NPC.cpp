#include "NPC.h"
#include "States.h"

#include <iostream>
#include <fstream>
#include <string>
#include "SDL_ttf.h"
#include <sstream>
#include "PlayerObject.h"
NPC::NPC(int x, int y, int z, int w, int h, WorldInfo *info) :
   CollideableObject(x, y, z, w, h, info)
{
   has_quest_symbol = new GameObject(x, y - (h / 2) - 35, 0, 40, 40, info);
   has_quest_symbol->setImage("materials/interaction/exclemation.png");
   has_quest_symbol->setVelocity(0, 50, 0);
   curState = NULL;
   last_spoken_to = 0;


   DialogueBox *test = new DialogueBox(info, glm::vec3(0, 0, 0), "this is the default text");
   test->setTalkingSprite("materials/test/noct.png");
   test->alignRight();
   curScene = new DialogueScene(info);
   curScene->addDialogueBox(test);
}

void NPC::render()
{
   if (hasQuest)
      has_quest_symbol->render();

   CollideableObject::render();
}

void  NPC::update(float dt)
{
   if (hasQuest) {
      has_quest_symbol->setWorldPos(worldX - has_quest_symbol->getWidth()/2, has_quest_symbol->getWorldY());
      float miny = worldY - (height / 2) - 35;
      float maxy = worldY - (height / 2) - 45;
      float cury = has_quest_symbol->getWorldY();

      float normd_dist = ((cury - maxy) / 10);
      if (normd_dist < 0.00001)
      {
         has_quest_symbol->setVelocity(velX, 35 + velY, 0);
      }
      else if (normd_dist > .9999)
      {
         has_quest_symbol->setVelocity(velX, -35 + velY, 0);
      }


      has_quest_symbol->update(dt);
   }

   if (interactionBegun && isInteractionFinished == false)
   {
      if (curScene->dialogueIsFinished())
         interactionFinished();
      setVelocity(0, 0, 0);
      curScene->update(dt);
   }
   else
   {
      curState = curState->update(dt);
   }




   CollideableObject::update(dt);
}

void NPC::interact() {
   if (isInteractionFinished == false)
      return;

   if (interactionBegun == false && ((SDL_GetTicks() - last_spoken_to) / 1000.0f) > 0.5)
   {
      isInteractionFinished = false;
      setVelocity(0, 0, 0);
      hasQuest = false;
      interactionBegun = true;
      curScene->start();
      info_ptr->player->setIsInteracting(true);
      isInteracting = true;
   }


}

void NPC::interactionFinished()
{
   curScene = curScene->getNextScene();
   last_spoken_to = SDL_GetTicks();
   isInteractionFinished = true;
   info_ptr->player->setIsInteracting(false);
   interactionBegun = false;
   isInteracting = false;
}

void NPC::setStates(std::vector <State *> in)
{
   if (in.size() == 0)
      std::cout << "NO STATES SET FORNPC " << name << "\n";
   states = in;
   if (curState == NULL)
      curState = states.at(0);
}


std::vector<State *> createStates(std::ifstream& fin, WorldInfo *info, NPC *tobind)
{
   std::vector<State *> out;
   std::string buffer;

   while (buffer != "ENDSTATES") {
      std::getline(fin, buffer);
      std::istringstream iss(buffer);
      // might use this later
      iss >> buffer;
      // name of state type
      iss >> buffer;

      if (buffer == "moveto")
      {
         float x, y, z, speed;
         iss >> x >> y >> z >> speed;
         std::cout << x << " " << y << " " << z << " " << speed << "\n";
         out.push_back(new MoveToState(tobind, NULL, glm::vec3(x, y, z), speed));
      }
      else if (buffer == "wait")
      {
         float time;
         iss >> time;
         std::cout << "creating wait" << time << "\n";
         out.push_back(new WaitState(tobind, time, NULL));
      }
   }

   // link the states so they go one at a time
   for (int i = 0; i < out.size() - 1; i++)
   {
      out.at(i)->setNextState(out.at(i + 1));
   }
   //set the last state to go back to first state
   out.at(out.size() - 1)->setNextState(out.at(0));

   return out;
}

void loadSceneData(std::ifstream& fin, DialogueScene *scene, std::string buffer, WorldInfo *info)
{
   DialogueBox *tempBox = new DialogueBox(info, glm::vec3(0,0,0), "");   
   std::string temp; 
   int curLine = 0;
   while (buffer.find("END ENTRY") == std::string::npos)
   {

      if (buffer.find("SPEAKER") != std::string::npos)
      {
         std::istringstream iss(buffer);
         iss >> buffer;
         iss >> buffer;
         while (!iss.eof()) {
            iss >> temp;
            buffer.append(" " + temp);
         }
      }
      else if (buffer.find("ALIGNED") != std::string::npos)
      {
         if (buffer.find("RIGHT") != std::string::npos)
            tempBox->alignRight();
         else if (buffer.find("LEFT") != std::string::npos)
            tempBox->alignLeft();
      }
      else if (buffer.find("SPRITE") != std::string::npos)
      {
         std::istringstream iss(buffer);
         iss >> buffer;
         iss >> buffer;
         tempBox->setTalkingSprite(buffer);
      }
      else if (buffer.find("LINE") != std::string::npos)
      {
         buffer.erase(buffer.begin(), buffer.begin() + 6);
         if (buffer.at(0) == ' ')
         {
            buffer.erase(buffer.begin(), buffer.begin() + 1);
         }
         if (curLine == 0)
         {
            tempBox->setText(buffer, 0);
            curLine++;
         }
         else
         {
            tempBox->addLineOfText(buffer);
         }
      }
      std::getline(fin, buffer);
   }
   scene->addDialogueBox(tempBox);
}


void loadSceneName(std::string buffer, DialogueScene *scene)
{
   std::string temp;
   if (buffer.find("DIALOGUE SCENE") != std::string::npos)
   {
      std::istringstream iss(buffer);
      iss >> buffer;
      iss >> buffer;
      iss >> buffer;
      while (!iss.eof()) {
         iss >> temp;
         buffer.append(" " + temp);
      }
      scene->setName(buffer);
   }

}

std::vector<DialogueScene *> loadDialogueScenes(std::ifstream& fin, WorldInfo * info, NPC *out)
{
   std::vector<DialogueScene *> scenes;
   std::string buffer;
   int numScenes = 1, i = 0;

   std::getline(fin, buffer);

   while (buffer.find("END DIALOGUE") == std::string::npos)  {
      scenes.push_back(new DialogueScene(info));
      loadSceneName(buffer, scenes.at(i));

      while (buffer.find("END SCENE") == std::string::npos) {
         loadSceneData(fin, scenes.at(i), buffer, info);
         std::getline(fin, buffer);
      }

      i++;
      std::getline(fin, buffer);
   }
   if(scenes.size() > 0)
      out->setDialogueScene(scenes.at(0));
   return scenes;
}

void loadDialogueProgress(std::ifstream& fin, std::vector<DialogueScene *> scenes)
{
   std::string buffer, temp1 = "", temp2 = "";
   DialogueScene *from, *to;
   std::getline(fin, buffer);
   std::istringstream iss(buffer);

   while (buffer.find("END PROGRESS") == std::string::npos)
   {
      // these whiles make sure that words with spaces are taken into account
      iss >> temp1;
      while (buffer != "->") {
         iss >> buffer;
         if (buffer != "->") // check that the string being appended isn't the next "to" symbol
            temp1.append(" " + buffer);
      }
      iss >> temp2;
      while (!iss.eof()) {
         iss >> buffer;
         temp2.append(" " + buffer);
      }

      // lookup the name of the scene we want to transition from
      for (int i = 0; i < scenes.size(); i++) {
         if (scenes.at(i)->getName() == temp1) {
            from = scenes.at(i);
         }
      }
      // lookup the name of the scene we want to transition to
      for (int i = 0; i < scenes.size(); i++) {
         if (scenes.at(i)->getName() == temp2) {
            to = scenes.at(i);
         }
      }

      from->setNextScene(to);
      std::getline(fin, buffer);
      std::istringstream iss(buffer);
   }
}

NPC * createNPCFromDatabase(std::ifstream& fin, WorldInfo *info)
{
   NPC *out;// = new NPC(0, 0, 0, 80, 80, info);
   std::string buffer, name, img_file;
   float x, y, z, w, h;
   
   // get the name and file location of sprite
   std::getline(fin, buffer);
   name = buffer;
   std::getline(fin, buffer);
   img_file = buffer;

   // read in the coordinates and size of sprite
   fin >> x >> y >> z >> w >> h;
   out = new NPC(x, y, z, w, h, info);
   out->setImage(img_file.c_str());
   out->setName(name);

   std::getline(fin, buffer);
   std::getline(fin, buffer);

   std::vector<DialogueScene *> scenes;
   while (buffer.find("END NPCDEF") == std::string::npos) {
      
      if (buffer.find("STATES") != std::string::npos) {
         out->setName(name);
         out->setStates(createStates(fin, info, out));
      }

      if (buffer.find("DIALOGUE DEF") != std::string::npos) {
         scenes = loadDialogueScenes(fin, info, out);
      }

      if (buffer.find("SCENE PROGRESS") != std::string::npos) {
         if (scenes.size() > 1) {
            loadDialogueProgress(fin, scenes);
         }
         
      }
      std::getline(fin, buffer);
   }
   return out;
}

std::vector<NPC*> NPCLoader(std::string in, WorldInfo *info) {
   std::vector<NPC *> out;
   std::ifstream fin(in);
   std::string buffer;



   if (!fin)
   {
      std::cout << "Could not open specified NPC database\n";
   }

   
   while (!fin.eof())
   {
      std::getline(fin, buffer);

      if (buffer.find("NPC") != std::string::npos)
      {
         out.push_back(createNPCFromDatabase(fin, info));
        // std::cout << "NPC BLOCK INCORRECT. 'NPC' required at beginning of block\n";
       //  std::cout << "got instead: \"" << buffer << "\"\n";
       //  return out;
      }
      else
      {
         std::cout << buffer << "\n";
      }
      
   }

   return out;
}
