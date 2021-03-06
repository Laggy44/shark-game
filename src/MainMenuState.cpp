#include "MainMenuState.h"
#include "PlayState.h"
#include "OptionsState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "Game.h"
#include "InputHandler.h"

const string MainMenuState::menuID = "MENU";

void MainMenuState::update(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->update();
    }
    startButton->update(); // start button has to be updated on its own
}
void MainMenuState::render(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->render();
    }
    startButton->render();
}

bool MainMenuState::onEnter(){

    cout << "Entering main menu." << endl;

    StateParser stateParser;
    stateParser.parseState("game.xml", menuID, &gameObjects, &textureIDList);

    SDL_SetRenderDrawColor(Game::getTheInstance()->getRenderer(), 255, 255, 255, 255); // white background

    callbacks.push_back(0);
    callbacks.push_back(startGame);
    callbacks.push_back(quitGame);
    callbacks.push_back(gotoOptions);
    setCallbacks();

    return true;
}
bool MainMenuState::onExit(){
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
    delete startButton;
    InputHandler::getTheInstance()->reset();
    return true;
}

void MainMenuState::quitGame(){
    Game::getTheInstance()->quitGame();
}
void MainMenuState::startGame(){
    Game::getTheInstance()->getStateHandler()->changeState(new PlayState());
}
void MainMenuState::gotoOptions(){
    Game::getTheInstance()->getStateHandler()->pushState(new OptionsState());
}

void MainMenuState::setCallbacks(){
    for (int i = 0; i < gameObjects.size(); i++){
        if (dynamic_cast<MenuButton*> (gameObjects[i])){ // if the item we're looking at is a menubutton
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setCallback(callbacks[button->getCallbackID()]);  // set the callback
            // we do this b/c start button needs to be updated by itself
            if (button->getTextureID() == "startbutton"){
                startButton = button;
                gameObjects.erase(gameObjects.begin() + i);
                i--;
            }
        }
    }
}
