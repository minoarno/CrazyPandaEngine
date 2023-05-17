#pragma once

class AudioTemplate
{
public:
	virtual ~AudioTemplate() {};
	virtual void PlaySound(int soundID) = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void StopAllSounds() = 0;
	virtual int AddSound(const std::string& file) = 0;
};

class Audio : public AudioTemplate
{
public:
	Audio();
	virtual ~Audio() = default;

	virtual void PlaySound(int soundID) override;
	virtual void StopSound(int soundID) override;
	virtual void StopAllSounds()override;
	virtual int AddSound(const std::string& file)override;
private:
	class MixerAudio;
	std::unique_ptr<MixerAudio> pimpl;
};

class NullAudio : public AudioTemplate
{
public:
	virtual void PlaySound(int) override {};
	virtual void StopSound(int) override {};
	virtual void StopAllSounds()override {};

	virtual int AddSound(const std::string&)override { return -1; };
};

