#pragma once
#include <stdio.h>
#include "EventReceiver.h"

namespace Valzuroid {
	namespace Pinball {
		namespace UI {
			[event_source(native)]
			class EventSource
			{
			protected:
				int eventNo = 0;
			public:
				inline void setEventNo(int eventNo){ this->eventNo = eventNo; }

				inline void Hook(EventReceiver* eventReceiver)
				{
					__hook(&EventSource::EventTrigger, this, &EventReceiver::Callback, eventReceiver);
				}

				__event void EventTrigger(int eventNo);
			};
		}
	}
}