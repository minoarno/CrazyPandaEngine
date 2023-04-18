#pragma once
#include "BaseComponent.h"

namespace dae
{
	class EventSubject;
	class EventObserver
	{
	public:
		virtual ~EventObserver() = default;

		virtual void OnNotify(EventSubject* pEventSubject) = 0;
	};
}

