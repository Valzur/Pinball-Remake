#include "Text.h"
using namespace Valzuroid::Pinball::UI;

Text::Text(Vector2D position, string text, int fontSize, string fontPath)
{
	if (fontPath.empty())
	{
		font.loadFromFile("Assets/Fonts/CHILLER.TTF");
	}
	else
	{
		font.loadFromFile(fontPath);
	}
	setString(text);
	setFont(font);
	setCharacterSize(fontSize);
	sf::FloatRect bounds = getLocalBounds();
	setOrigin(bounds.left + bounds.width / 2.0, bounds.top + bounds.height / 2.0);
	setPosition(position);
}

void Text::updateTick(){}

void Text::draw(Interface& interface)
{
	interface.GetWindow().draw(*this);
}