#include "PlayState.h"
#include "Level.h"
#include "StateParser.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "BulletHandler.h"
#include "PauseState.h"
#include <sstream>

const string PlayState::playID = "PLAY";

void PlayState::update(){
    level->update();
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_ESCAPE)){
        pauseGame();
    }
}
void PlayState::render(){
    level->render();
}

bool PlayState::onEnter(){
    /**BE ABSOLUTELY SURE THAT MARGIN AND SPACING IN THE LEVEL FILE ARE NOT ZERO**/
    LevelParser levelParser;
    string levelFile = "Assets/level_";
    stringstream s;
    s << Game::getTheInstance()->getCurrentLevel() << ".tmx";
    levelFile += s.str();
    level = levelParser.parseLevel(levelFile.c_str());
    /**YOU WILL GET A DIVISION BY ZERO AND THE PROGRAM WILL NOT LAUNCH**/

    SDL_Color backgroundColor = {46, 116, 191, 255};
    SDL_SetRenderDrawColor(Game::getTheInstance()->getRenderer(), backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

    BulletHandler::getTheInstance()->setCollisionLayers(level->getCollisionLayers());
    cout << "Entering playstate" << endl;
    return true;
}
bool PlayState::onExit(){
    InputHandler::getTheInstance()->reset();
    return true;
}

void PlayState::pauseGame(){
    Game::getTheInstance()->getStateHandler()->pushState(new PauseState());
}
