#include "MiniginPCH.h"
#include "AudioManager.h"

#include "SDL_mixer.h"
#include "ResourceManager.h"
#include <future>

//https://cpppatterns.com/patterns/pimpl.html
class Audio::MixerAudio
{
public:
	MixerAudio();
	~MixerAudio();

	void PlaySound(int soundID);
	void StopSound(int soundID);
	void StopAllSounds();

	int AddSound(const std::string& file);
private:
	std::vector<Mix_Chunk*> m_pSoundEffects;

	int m_Audio_Channels = 2;
};

Audio::Audio()
	:pimpl{ std::make_unique<MixerAudio>() }
{
}

void Audio::PlaySound(int soundID)
{
	pimpl->PlaySound(soundID);

}

void Audio::StopSound(int soundID)
{
	pimpl->StopSound(soundID);
}

void Audio::StopAllSounds()
{
	pimpl->StopAllSounds();
}

int Audio::AddSound(const std::string& file)
{
	return pimpl->AddSound(file);
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
		std::cout << "Sound out of range.\n";
		return;
	}
	std::thread tempThread{ [=]()
	{
		Mix_PlayChannel(-1, m_pSoundEffects[soundID], 0);
	} };
	tempThread.join();
}

void Audio::MixerAudio::StopSound(int soundID)
{
	if (soundID >= int(m_pSoundEffects.size()))
	{
		std::cout << "Sound out of range.\n";
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

	std::cout << "The sound is currently not being played.\n";
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
		std::cout << (m_pSoundEffects.size() - 1) << " Sound is Ready, path: " << file << '\n';
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize audio: %s", Mix_GetError());

	}
	return 0;
}
