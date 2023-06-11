#pragma once
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class EventObserver;

	class EventSubject
	{
	public:
		EventSubject() = default;
		~EventSubject() = default;

		EventSubject(const EventSubject& other) = delete;
		EventSubject& operator=(const EventSubject& other) = delete;
		EventSubject(EventSubject&& other) = delete;
		EventSubject& operator=(EventSubject&& other) = delete;

		void AddObserver(EventObserver* observer);
		void RemoveObserver(EventObserver* observer);
	protected:
		void Notify(EventSubject* pBaseComponent);

	private:
		std::vector<EventObserver*> m_pObservers{};
		int m_AmountObservers = 0;
	};
}