#include "PauseState.h"
#include "Game.h"
#include "StateParser.h"
#include "MainMenuState.h"
#include "TextureHandler.h"
#include "InputHandler.h"

const string PauseState::pauseID = "PAUSE";


void PauseState::update(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->update();
    }
    mainmenuButton->update();
}
void PauseState::render(){

    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->render();
    }
    mainmenuButton->render();

}

bool PauseState::onEnter(){
    cout << "Entering pause" << endl;
    StateParser stateParser;
    stateParser.parseState("game.xml", pauseID, &gameObjects, &textureIDList);

    SDL_SetRenderDrawColor(Game::getTheInstance()->getRenderer(), 255, 255, 255, 255); // white background

    callbacks.push_back(0);
    callbacks.push_back(quitGame);
    callbacks.push_back(resumeGame);
    callbacks.push_back(gotoMainMenu);
    setCallbacks();

    return true;
}
bool PauseState::onExit(){
    cout << "Exiting pause" << endl;
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
    for (int i = 0; i < textureIDList.size(); i++){
        TextureHandler::getTheInstance()->removeFromTextureMap(textureIDList[i]);
    }
    InputHandler::getTheInstance()->reset();
    return true;
}


void PauseState::setCallbacks(){
    for (int i = 0; i < gameObjects.size(); i++){
        if (dynamic_cast<MenuButton*> (gameObjects[i])){ // if the item we're looking at is a menubutton
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setCallback(callbacks[button->getCallbackID()]);  // set the callback
            if (button->getTextureID() == "mainmenubutton"){
                mainmenuButton = button;
                gameObjects.erase(gameObjects.begin() + i);
                i--;
            }
        }
    }
}

void PauseState::quitGame(){
    Game::getTheInstance()->quitGame();
}

void PauseState::resumeGame(){
    //reset color
    SDL_Color backgroundColor = {46, 116, 191, 255};
    SDL_SetRenderDrawColor(Game::getTheInstance()->getRenderer(), backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    Game::getTheInstance()->getStateHandler()->popState();
}

void PauseState::gotoMainMenu(){
    Game::getTheInstance()->getStateHandler()->popState(); // close pause state
    Game::getTheInstance()->getStateHandler()->changeState(new MainMenuState());
}
