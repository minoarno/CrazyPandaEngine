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

	inline double GetTimeScale()const { return m_TimeScale; }
	inline double GetElapsedSeconds()const { return m_ElapsedSeconds * m_TimeScale; }
	inline double GetFixedElapsedSeconds()const { return m_FixedElapsedSeconds * m_TimeScale; }
	inline double GetTotalSeconds()const { return m_TotalSeconds; }

	inline void SetTimeScale(const double value) { m_TimeScale = value; }
	inline void SetElapsedSeconds(const double value) { m_ElapsedSeconds = value; }
	inline void AddToTotalSeconds(const double value) { m_TotalSeconds += value; }
	inline void SetFixedElapsedSeconds(const double value) { m_FixedElapsedSeconds = value; }
private:
	friend class Singleton<Time>;
	Time() = default;

	double m_TimeScale = 1.f;
	double m_TotalSeconds = 0.f;
	double m_ElapsedSeconds = 0.f;
	double m_FixedElapsedSeconds = 0.02f;
};

