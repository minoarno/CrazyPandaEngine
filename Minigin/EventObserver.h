#pragma once
#include "BaseComponent.h"

namespace dae
{
	class EventSubject;
	class EventObserver
	{
	public:
		EventObserver() = default;
		EventObserver(const EventObserver&) = delete;
		EventObserver& operator=(const EventObserver&) = delete;
		EventObserver(EventObserver&&) = delete;
		EventObserver& operator=(EventObserver&&) = delete;
		virtual ~EventObserver() = default;

		virtual void OnNotify(EventSubject* pEventSubject) = 0;
	};
}
