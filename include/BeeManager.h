#ifndef BEE_MANAGER_H
#define BEE_MANAGER_H

#include "Bee.h"
#include <vector>

class BeeManager
{
    public:
        std::vector<Bee> bees;

        int screenWidth;
        int screenHeight;

        float timer;
        float spawnInterval;

        // Constructor
        BeeManager(int screenWidth, int screenHeight, float spawnInterval = 5.0f);

        void Update(float deltaTime);
        void Draw();
        void Unload();
        int BeesPassed();

    private:
        void SpawnBee();
        int beesPassed;
};

#endif