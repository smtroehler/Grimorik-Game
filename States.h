#pragma once

#include "NPC.h"

class TestNPCState : public State
{
public:
   TestNPCState(NPC *bind);
   NPC *toMove;
   virtual State *update(float dt);
   glm::vec3 startPos;



};

class MoveToState : public State
{
public:
   MoveToState(NPC *bind, State *nextState, glm::vec3 MoveTo, float spd);
   virtual State *update(float dt);

   NPC *toMove;
   float speed;
   glm::vec3 dest;
   State *nextState;

   virtual void setNextState(State *toSet) { nextState = toSet; }
};

class WaitState : public State
{
public:
   WaitState(NPC *bind, float timeToWait, State *nextState);
   NPC *toMove;
   virtual State *update(float dt);
   glm::vec3 startPos;
   State *nextState;

   float timeToWait;
   float elapsedTime;

   virtual void setNextState(State *toSet) { nextState = toSet; }
};