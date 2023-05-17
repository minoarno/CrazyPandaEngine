#pragma once
#include "AudioManager.h"

//https://gameprogrammingpatterns.com/service-locator.html
class ServiceLocator
{
public:
    static void Initialize();
    static AudioTemplate& GetAudio();
    static void Provide(AudioTemplate* service);
    static void CleanUp();
private:
    static AudioTemplate* m_pAudioManagerService;
    static NullAudio m_NullAudioService;
};