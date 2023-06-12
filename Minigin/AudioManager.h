#pragma once
#include <string>
#include <memory>
#include <queue>
#include <mutex>

class AudioTemplate
{
public:
	virtual ~AudioTemplate() {};
	virtual void PlaySound(int soundID) = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void StopAllSounds() = 0;
	virtual int AddSound(const std::string& file) = 0;
};

//Audio manager was inspired by Aaron Frans, Jonas Bruylant and the labo feedback
class Audio : public AudioTemplate
{
public:
	Audio();
	virtual ~Audio();

	virtual void PlaySound(int soundID) override;
	virtual void StopSound(int soundID) override;
	virtual void StopAllSounds()override;
	virtual int AddSound(const std::string& file)override;
private:
	class MixerAudio;
	std::unique_ptr<MixerAudio> pimpl;

	std::queue<int> m_SoundEventQueue;

	void RunThread();

	//Multi threading
	std::atomic<bool> m_IsThreadRunning{ true };
	std::mutex m_Mutex;
	std::condition_variable m_QueueCondition;
	std::jthread m_SoundThread;
};

class NullAudio : public AudioTemplate
{
public:
	virtual void PlaySound(int) override {};
	virtual void StopSound(int) override {};
	virtual void StopAllSounds()override {};

	virtual int AddSound(const std::string&)override { return -1; };
};

