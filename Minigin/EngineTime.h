#pragma once
#include "Singleton.h"
class Time final : public dae::Singleton<Time>
{
public:
	~Time() = default;

	Time(const Time& other) = delete;
	Time& operator=(const Time& other) = delete;
	Time(Time&& other) = delete;
	Time& operator=(Time&& other) = delete;

	[[nodiscard]] double GetTimeScale()const { return m_TimeScale; }
	[[nodiscard]] double GetElapsedSeconds()const { return m_ElapsedSeconds * m_TimeScale; }
	[[nodiscard]] double GetFixedElapsedSeconds()const { return m_FixedElapsedSeconds * m_TimeScale; }
	[[nodiscard]] double GetTotalSeconds()const { return m_TotalSeconds; }

	void SetTimeScale(const double value) { m_TimeScale = value; }
	void SetElapsedSeconds(const double value) { m_ElapsedSeconds = value; }
	void AddToTotalSeconds(const double value) { m_TotalSeconds += value; }
	void SetFixedElapsedSeconds(const double value) { m_FixedElapsedSeconds = value; }
private:
	friend class Singleton<Time>;
	Time() = default;

	double m_TimeScale = 1.f;
	double m_TotalSeconds = 0.f;
	double m_ElapsedSeconds = 0.f;
	double m_FixedElapsedSeconds = 0.02f;
};

