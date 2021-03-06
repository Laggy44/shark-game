#include "GameStateHandler.h"

void GameStateHandler::update(){
  states.back()->update();
}

void GameStateHandler::render(){
  states.back()->render();
}

void GameStateHandler::pushState(GameState* state){
  states.push_back(state);
  states.back()->onEnter();
}

void GameStateHandler::changeState(GameState* state){
  if (!states.empty()){
    states.back()->onExit(); // delete the current state
    delete states.back();
    states.pop_back();
  }
  state->onEnter();
  states.push_back(state); // add the new one
}

void GameStateHandler::popState(){
  if (!states.empty()){
    states.back()->onExit();
    delete states.back();
    states.pop_back();
  }
}
