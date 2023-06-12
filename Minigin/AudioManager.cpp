#include "MiniginPCH.h"
#include "AudioManager.h"

#include "SDL_mixer.h"
#include "ResourceManager.h"
#include <future>

#include <mutex>
#include <condition_variable>
#include <thread>


//https://cpppatterns.com/patterns/pimpl.html
class Audio::MixerAudio
{
public:
	MixerAudio();
	~MixerAudio();

	void PlaySound(int soundID);
	void StopSound(int soundID);
	void MuteAllSounds();
	void StopAllSounds();

	int AddSound(const std::string& file);
private:
	std::vector<Mix_Chunk*> m_pSoundEffects;

	int m_Audio_Channels = 2;
};

Audio::Audio()
	:pimpl{ std::make_unique<MixerAudio>() }
{
	m_SoundThread = std::jthread(&Audio::RunThread, this);
}

Audio::~Audio()
{
	m_IsThreadRunning = false;
	m_QueueCondition.notify_all();
}

void Audio::PlaySound(int soundID)
{
	std::lock_guard<std::mutex> guardLock(m_Mutex);
	m_SoundEventQueue.push(soundID);
	m_QueueCondition.notify_all();
}

void Audio::StopSound(int soundID)
{
	pimpl->StopSound(soundID);
}

void Audio::MuteAllSounds()
{
	pimpl->MuteAllSounds();
}

void Audio::StopAllSounds()
{
	pimpl->StopAllSounds();
}

int Audio::AddSound(const std::string& file)
{
	return pimpl->AddSound(file);
}

void Audio::RunThread()
{
	while (m_IsThreadRunning)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		m_QueueCondition.wait(lock, [&]()
			{
				if (!m_IsThreadRunning)	return true;

				return !m_SoundEventQueue.empty();
			});

		if (m_SoundEventQueue.empty() || !m_IsThreadRunning) return;

		int soundIndex = m_SoundEventQueue.front();
		m_SoundEventQueue.pop();
		
		lock.unlock();

		pimpl->PlaySound(soundIndex);
	}
}

Audio::MixerAudio::MixerAudio()
{
	//Initialize sound
	////https://youtu.be/q06uSmkiqec

	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	UINT16 audio_format = AUDIO_S16SYS;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, m_Audio_Channels, audio_buffers) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize audio: %s", Mix_GetError());
	}

}

Audio::MixerAudio::~MixerAudio()
{
	for (Mix_Chunk* e : m_pSoundEffects)
	{
		Mix_FreeChunk(e);
		//delete e;
		e = nullptr;
	}
	m_pSoundEffects.clear();

	Mix_CloseAudio();
}

void Audio::MixerAudio::PlaySound(int soundID)
{
	if (soundID >= int(m_pSoundEffects.size()))
	{
		Log::CoreWarning("Sound out of range.");
		return;
	}

	Mix_PlayChannel(-1, m_pSoundEffects[soundID], 0);
}

void Audio::MixerAudio::StopSound(int soundID)
{
	if (soundID >= int(m_pSoundEffects.size()))
	{
		Log::CoreWarning("Sound out of range.");
		return;
	}

	for (int i = 0; i < m_Audio_Channels; i++)
	{
		if (Mix_GetChunk(i) == m_pSoundEffects[soundID])
		{
			Mix_HaltChannel(i);
			return;
		}
	}

	Log::CoreWarning("The sound is currently not being played.");
}

void Audio::MixerAudio::MuteAllSounds()
{
	Mix_Volume(-1, 0);
}

void Audio::MixerAudio::StopAllSounds()
{
	Mix_HaltChannel(-1);
}

int Audio::MixerAudio::AddSound(const std::string& file)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV((dae::ResourceManager::GetInstance().GetDataPath() + file).c_str());

	if (tmpChunk != nullptr)
	{
		m_pSoundEffects.push_back(tmpChunk);
		Log::CoreInfo(std::to_string(m_pSoundEffects.size() - 1) + " Sound is Ready, path: " + file);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize audio: %s", Mix_GetError());
	}
	return 0;
}
