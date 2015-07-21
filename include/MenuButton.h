#ifndef MENUBUTTON_H
#define MENUBUTTON_H

class MenuButton : public GameObject {

  public:
    void update();
    void render();
  private:
    void (*callback)();
  
};

class ButtonCreator : public BaseCreator {
  GameObject* createGameObject() const {
    return new MenuButton();
  }
};

#endif