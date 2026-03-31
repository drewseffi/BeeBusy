#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "raylib.h"
#include <map>

enum SoundType
{
    SFX_PICKUP,
    SFX_PLANT,
    SFX_PLANT_DESTORY,
    SFX_SEED,
    SFX_GAME_OVER
};

class SoundManager
{
    public:
        Music bgMusic;

        void Load();
        void Update();
        void Play(SoundType type);
        void BackgroundMusic();
        void Unload();

    private:
        std::map<SoundType, Sound> sounds;
};

#endif