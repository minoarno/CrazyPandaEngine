#include "MiniginPCH.h"
#include "ServiceLocator.h"

NullAudio ServiceLocator::m_NullAudioService{};
AudioTemplate* ServiceLocator::m_pAudioManagerService{ &m_NullAudioService };

void ServiceLocator::Initialize()
{
    m_pAudioManagerService = &m_NullAudioService;
}

AudioTemplate& ServiceLocator::GetAudio()
{
    return *m_pAudioManagerService;
}

void ServiceLocator::Provide(AudioTemplate* service)
{
    if (service == NULL)
    {
        // Revert to null service.
        m_pAudioManagerService = &m_NullAudioService;
    }
    else
    {
        m_pAudioManagerService = service;
    }
}

void ServiceLocator::CleanUp()
{
    delete m_pAudioManagerService;
    m_pAudioManagerService = nullptr;
}
