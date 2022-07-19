#include "UIManager.h"
using namespace Valzuroid::Pinball::UI;

void UIManager::draw(Interface& interface)
{
    UIElement** allObjects = GetAllObjects();
	for (int i = 0; i < Count(); i++)
	{
		allObjects[i]->draw(interface);
	}
}

UIManager::UIManager()
{
}

void UIManager::onMouseClickEvent(sf::Vector2i mousePosition)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == wasClicked) return;

    UIElement** allObjects = GetAllObjects();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        wasClicked = true;
        for (int i = 0; i < Count(); i++)
        {
            allObjects[i]->onMouseButtonDown(mousePosition);
        }
        return;
    }

    wasClicked = false;
    for (int i = 0; i < Count(); i++)
    {
        allObjects[i]->onMouseButtonUp(mousePosition);
    }
}
