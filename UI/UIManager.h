#pragma once
#include "../UI/UIElement.h"
#include "../Utility/Factory.h"
#include "../UI/Button.h"

namespace Valzuroid {
	namespace Pinball {
		using namespace Utility;
		namespace UI {
			class UIManager : public Factory<UIElement>
			{
			private:
				bool wasClicked = false;
			public:
				UIManager();
				void draw(Interface& interface);
				void onMouseClickEvent(sf::Vector2i mousePosition);
			};
		}
	}
}