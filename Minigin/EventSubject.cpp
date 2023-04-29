#include "MiniginPCH.h"
#include "EventSubject.h"
#include "EventObserver.h"

void dae::EventSubject::AddObserver(dae::EventObserver* observer)
{
	m_pObservers.push_back(observer);
	m_AmountObservers++;
}

void dae::EventSubject::RemoveObserver(dae::EventObserver* observer)
{
	auto it = m_pObservers.begin();
	while (it != m_pObservers.end())
	{
		if (*it == observer)
		{
			it = m_pObservers.erase(it);
			m_AmountObservers--;
		}
		else
		{
			++it;
		}
	}
}

void dae::EventSubject::Notify(dae::EventSubject* pBaseComponent)
{
	for (int i = 0; i < m_AmountObservers; i++)
	{
		m_pObservers[i]->OnNotify(pBaseComponent);
	}
}