#ifndef MENUSTATE_H
#define MENUSTATE_H

class MenuState : public GameState {

  public:
    virtual ~MainMenuState(){};
  protected:
    vector <void(*callback)> callbacks;
};

#endif