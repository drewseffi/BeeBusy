#ifndef POT_MANAGER_H
#define POT_MANAGER_H

#include "Flowerpot.h"
#include <vector>

class PotManager
{
    public:
        std::vector<Flowerpot> pots;

        int screenWidth;
        int screenHeight;
        int initialPotCount;

        Texture2D potTexture;
        Texture2D plantTexture;

        // Constructor
        PotManager(int screenWidth, int screenHeight, int intitialPotCount);

        void Update(float deltaTime);
        void Draw();
        void Unload();
        void SpawnNewPot();
        void SpawnInitialPots();

};

#endif