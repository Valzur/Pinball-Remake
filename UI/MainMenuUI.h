#pragma once
#include "UIElement.h"
#include "../Utility/Factory.h"
#include "AllUIIncludes.h"


namespace Valzuroid {
	namespace Pinball {
		using namespace UI;
		using namespace Utility;
		class Game;

		namespace UI {
			class MainMenuIU : public Factory<UIElement>, public UIElement, EventReceiver
			{
			private:
				bool wasClicked = false;
				Game* gameReference;

				void ExitGame();
			public:
				MainMenuIU(Game* gameReference = nullptr);

				void Callback(int eventNo) override;
				void onMouseClickEvent(sf::Vector2i mousePosition);
				void updateTick() override;
				void draw(Interface& interface) override;
			};
		}
	}
}