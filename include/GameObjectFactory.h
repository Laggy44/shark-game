#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <string>
#include <map>

using namespace std;

class BaseCreator {
  public:
    GameObject* createGameObject() const = 0;
    virtual ~BaseCreator(){};
};

class GameObjectFactory {

  public:
    GameObjectFactory* getTheInstance();
    bool registerType(string, BaseCreator*)
    GameObject* create(string);
  private:
    GameObjectFactory(){};
    ~GameObjectFactory(){};
    static GameObjectFactory* theInstance;
    map<string, BaseCreator*> creators;


};

#endif