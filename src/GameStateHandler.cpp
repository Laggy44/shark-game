#include "GameStateHandler.h"

void GameStateHandler::update(){
  states.back()->update();
}

void GameStateHandler::render(){
  states.back()->render();
}

void GameStateHandler::pushState(GameState* state){
  states.push_back(state);
  states.back()->sonEnter();
}

void GameStateHandler::changeState(GameState* state){
  if (!states.empty()){
    if (states.back()->getStateID == state->getStateID()){ // if we're passing the current state through, somebody fucked up
        return;
    }
    states.back()->onExit(); // delete the current state
    states.pop_back();
    states.clear();
  }
  states.push_back(state); // add the new one
  states.back()->onEnter(); 
}

void GameStateHandler::popState(){
  if (!states.empty()){
    states.back()->onExit();
    states.pop_back();
  }
}