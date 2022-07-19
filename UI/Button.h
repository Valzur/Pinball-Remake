#pragma once
#include "UIElement.h"
#include "Text.h"
#include <stdio.h>
#include "EventSource.h"

namespace Valzuroid {
	namespace Pinball{
		namespace UI{
			class Button : public UIElement, public Text, public EventSource
			{
			private:
				const sf::Color clickedColor = sf::Color(42, 157, 143);
				const sf::Color unClickedColor = sf::Color(210, 210, 210);

				int width, height;

				bool isClicked = false;
			public:
				Button(Vector2D position, int width, int height, string text = "", int fontSize = 42, string fontPath = "");

				void draw(Interface& interface) override;
				void onMouseButtonDown(sf::Vector2i mousePosition) override;
				void onMouseButtonUp(sf::Vector2i mousePosition) override;
				inline void updateTick() override {};
			};
		}
	}
}