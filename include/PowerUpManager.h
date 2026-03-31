#ifndef POWER_UP_MANAGER_H
#define POWER_UP_MANAGER_H

#include "PowerUp.h"
#include <vector>

class PowerUpManager
{
    public:
        std::vector<PowerUp> powerUps;

        int screenWidth;
        int screenHeight;

        Texture2D speedTexture;
        Texture2D fillTexture;
        Texture2D doubleTexture;

        /**
         * If I want to have more interesting spawn mechanics duration can be removed as
         * powerup also has a duration variable for sake of scalability
         */
        float duration;
        float timer;

        // Constructor
        PowerUpManager(int screenWidth, int screenHeight, float duration);

        void Update(float deltaTime);
        void Draw();
        void Unload();
    
    private:
        void SpawnPowerup(float duration);
        void DespawnPowerup();

        float respawnTimer;
};

#endif