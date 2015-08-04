#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <vector>
#include "Bullet.h"

using namespace std;

class BulletHandler{
    public:
        static BulletHandler* getTheInstance();

        void update();
        void render();

        void setCollisionLayers(vector<TileLayer*>* cl)
        { collisionLayers = cl; };

        void addPlayerBullet(int,int,float);

        vector<Bullet*> getPlayerBullets()
        { return playerBullets; };

    private:
        BulletHandler(){};
        static BulletHandler* theInstance;
        vector<TileLayer*>* collisionLayers;
        vector<Bullet*> playerBullets;
        const float BULLET_SPEED = 2000.0f;
        const int BULLET_SIZE = 6;

        void updatePlayerBullets();
        void renderPlayerBullets();
};

#endif
