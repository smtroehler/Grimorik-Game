#include "NPC.h"
#include "States.h"

#include <iostream>
#include <fstream>
#include <string>
#include "SDL_ttf.h"
#include <sstream>
NPC::NPC(int x, int y, int z, int w, int h, WorldInfo *info) :
   CollideableObject(x, y, z, w, h, info)
{
   has_quest_symbol = new GameObject(x, y - (h / 2) - 35, 0, 40, 40, info);
   has_quest_symbol->setImage("materials/interaction/exclemation.png");
   has_quest_symbol->setVelocity(0, 50, 0);
   curState = NULL;
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

   curState = curState->update(dt);





   CollideableObject::update(dt);
}

void NPC::interact()
{

   
}

void NPC::interactionFinished()
{

}

void NPC::setStates(std::vector <State *> in)
{
   if (in.size() == 0)
      std::cout << "NO STATES SET FORNPC " << name << "\n";
   states = in;
   if (curState == NULL)
      curState = states.at(0);
}

NPCTEST::NPCTEST(int x, int y, int z, int w, int h, WorldInfo *info) :
   NPC(x, y, z, w, h, info)
{

   has_quest_symbol = new GameObject(x, y - (h / 2) - 35 , 0, 40, 40, info);
   has_quest_symbol->setImage("materials/interaction/exclemation.png");
   has_quest_symbol->setVelocity(0, 50, 0);

   State *moveLeft, *stop_p1, *moveRight, *stop_p2;
   states.push_back(new MoveToState(this, NULL, glm::vec3(0, 0, 0), 50));
   states.push_back(new MoveToState(this, NULL, glm::vec3(600, 0, 0), 50));
   states.push_back(new WaitState(this, 2.0f, NULL));
   states.push_back(new WaitState(this, 2.0f, NULL));

   curState = states.at(0);
   states.at(0)->setNextState(states.at(1));
   states.at(1)->setNextState(states.at(2));
   states.at(2)->setNextState(states.at(3));
   states.at(3)->setNextState(states.at(0));

   name = "I have no name";



   testscene = new DialogueScene(info);
   test = new DialogueBox(info, glm::vec3(0, 0, 0), "hello tehre testing new lines");
   test->setTalkingSprite("materials/test/noct.png");
   test->addLineOfText("this is on a new line");

   testscene->addDialogueBox(test);

   test = new DialogueBox(info, glm::vec3(0, 0, 0), "this is a test of multiple dialogs");
   test->setTalkingSprite("materials/test/noct.png");
   test->addLineOfText("character is aligned on the other side");
   test->alignLeft();

   testscene->addDialogueBox(test);

   test = new DialogueBox(info, glm::vec3(0, 0, 0), "this is a third test");
   test->setTalkingSprite("materials/test/noct.png");
   test->addLineOfText("here we will test a third line");
   test->addLineOfText("here is the third line");
   test->alignRight();

   testscene->addDialogueBox(test);
}

void NPCTEST::render()
{
   if (hasQuest)
      has_quest_symbol->render();


   CollideableObject::render();
}

void NPCTEST::update(float dt)
{

   if (hasQuest) {
      has_quest_symbol->setWorldPos(worldX - has_quest_symbol->getWidth() / 2, has_quest_symbol->getWorldY());
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
      if (info_ptr->cur_dialogue->dialogueIsFinished())
         interactionFinished();
      setVelocity(0, 0, 0);
   }
   else
   {
      curState = curState->update(dt);
   }

   CollideableObject::update(dt);
}


void NPCTEST::interact() {
   if (isInteractionFinished == false)
      return;

   if (interactionBegun == false)
   {
      prevVelocity = getVelocity();
      isInteractionFinished = false;
      setVelocity(0, 0, 0);
      info_ptr->cur_dialogue = testscene;
      std::cout << name << ": I have a quest for you!\n";
      hasQuest = false;
      interactionBegun = true;
   }


}

void NPCTEST::interactionFinished() {

   setVelocity(prevVelocity);
   isInteractionFinished = true;
   info_ptr->cur_dialogue = NULL;
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


   while (buffer != "ENDNPCDEF") {
      if (buffer == "STATES")
      {
         std::cout << "setting states\n";
         out->setName(name);
         out->setStates(createStates(fin, info, out));
      }
      if (buffer == "DIALOGUE")
      {
         std::cout << "loading dialogue\n";
         while (buffer != "ENDDIALOGUE")
         {
            fin >> buffer;
         }
         
      }
      fin >> buffer;
   }
   std::cout << "finished loading npc\n";
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
      if (buffer != "NPC")
      {
         std::cout << "NPC BLOCK INCORRECT. 'NPC' required at beginning of block\n";
         std::cout << "got instead: \"" << buffer << "\"\n";
         return out;
      }
      else
      {
         out.push_back(createNPCFromDatabase(fin, info));
      }

   }

   return out;
}
