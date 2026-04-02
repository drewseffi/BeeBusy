#include "SoundManager.h"

void SoundManager::Load()
{
    sounds[SFX_PICKUP] = LoadSound("assets/audio/powerUp.wav");
    sounds[SFX_PLANT] = LoadSound("assets/audio/plant.wav");
    sounds[SFX_PLANT_DESTORY] = LoadSound("assets/audio/plantDestroy.wav");
    sounds[SFX_SEED] = LoadSound("assets/audio/seed.wav");
    sounds[SFX_GAME_OVER] = LoadSound("assets/audio/gameOver.wav");

    bgMusic = LoadMusicStream("assets/audio/bgMusic.wav");
}

void SoundManager::Update(int sfxVol, int musicVol)
{
    for (auto &sound : sounds)
    {
        SetSoundVolume(sound.second, sfxVol / 100.0f);
    }

    SetMusicVolume(bgMusic, musicVol / 100.0f);
    UpdateMusicStream(bgMusic);
}

void SoundManager::BackgroundMusic()
{
    PlayMusicStream(bgMusic);
}

void SoundManager::Play(SoundType type)
{
    PlaySound(sounds[type]);
}

void SoundManager::Unload()
{
    for (auto &s : sounds)
    {
        UnloadSound(s.second);
    }
    UnloadMusicStream(bgMusic);
}