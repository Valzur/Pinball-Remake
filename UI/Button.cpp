#include "Button.h"
using namespace Valzuroid::Pinball::UI;

Button::Button(Vector2D position, int width, int height, string text, int fontSize, string fontPath): Text(position, text, fontSize, fontPath)
{
	this->width = width;
	this->height = height;
}

void Button::onMouseButtonDown(sf::Vector2i mousePosition)
{
	//cout << "Mouse Position: " << mousePosition.x << " : " << mousePosition.y << endl;
	//cout << "Button Position: " << getPosition().x << " : " << getPosition().y << endl;

	if (mousePosition.x < (getPosition().x + 0.5 * width) &&
		mousePosition.x > (getPosition().x - 0.5 * width) &&
		mousePosition.y > (getPosition().y - 0.5 * height) &&
		mousePosition.y < (getPosition().y + 0.5 * height))
	{
		isClicked = true;
	}
}

void Button::onMouseButtonUp(sf::Vector2i mousePosition)
{
	if (mousePosition.x < (getPosition().x + 0.5 * width) &&
		mousePosition.x >(getPosition().x - 0.5 * width) &&
		mousePosition.y > (getPosition().y - 0.5 * height) &&
		mousePosition.y < (getPosition().y + 0.5 * height) &&
		isClicked)
	{
		EventTrigger(eventNo);
	}
	isClicked = false;
}

void Button::draw(Interface& interface) 
{
	sf::RectangleShape button = sf::RectangleShape(sf::Vector2f(width, height));
	button.setFillColor(isClicked? clickedColor : unClickedColor);
	button.setOrigin(width / 2.0, height / 2.0);
	button.setPosition(getPosition());
	//cout << "Positon: " << getPosition().x << " | " << getPosition().y << endl;

	interface.GetWindow().draw(button);
	interface.GetWindow().draw(*this);
}