#pragma once
#include "EventSubject.h"


class Lives final : public dae::EventSubject
{
public:
	Lives(int amount);
	Lives(const Lives& other) = delete;
	Lives& operator=(const Lives& other) = delete;
	Lives(Lives&& other) = delete;
	Lives& operator=(Lives&& other) = delete;
	~Lives() = default;

	void LoseLife();
	void GainLife();

	int GetLives()const { return m_AmountOfLives; }
private:
	int m_AmountOfLives = 0;
};