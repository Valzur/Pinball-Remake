#pragma once
#include <stdio.h>
#include <iostream>
using namespace Valzuroid::Pinball::UI;

namespace Valzuroid {
	namespace Pinball {
		namespace UI {
			[event_receiver(native)]
			class EventReceiver
			{
			public:
				inline virtual void Callback(int eventNo) {};
			};
		}
	}
}