#include "MainMenuUI.h"

void MainMenuIU::draw(Interface& interface)
{
    sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, GAME_HEIGHT));
    background.setFillColor(sf::Color(48, 48, 54));
    interface.GetWindow().draw(background);

    UIElement** allObjects = GetAllObjects();
    for (int i = 0; i < Count(); i++)
    {
        allObjects[i]->draw(interface);
    }
}

MainMenuIU::MainMenuIU(Game* gameReference)
{
    this->gameReference = gameReference;

    //Header
    Text* header = new Text({WINDOW_WIDTH / 2.0, 150}, "PINBALL", 96, "Assets/Fonts/CHILLER.TTF");
    header->setFillColor(sf::Color(48, 188, 237));
    AddObject(header);

    Text* newSign = new Text({ WINDOW_WIDTH / 2.0 + 140, 125 }, "NEW!", 42, "Assets/Fonts/CHILLER.TTF");
    newSign->setFillColor(sf::Color(210, 210, 210));
    newSign->rotate(45);
    AddObject(newSign);

    Button* startButton = new Button(
        {WINDOW_WIDTH / 2.0, 280}, 
        400,
        40,
        "Start",
        28, 
        "Assets/Fonts/Atkinson-Hyperlegible-Regular.ttf");
    startButton->setFillColor(sf::Color(42, 157, 143));
    startButton->Hook( (EventReceiver*)gameReference);
    AddObject(startButton);

    Button* exitButton = new Button(
        { WINDOW_WIDTH / 2.0, 360 },
        400,
        40,
        "Exit",
        28,
        "Assets/Fonts/Atkinson-Hyperlegible-Regular.ttf");
    exitButton->setFillColor(sf::Color(42, 157, 143));
    exitButton->setEventNo(-1);
    exitButton->Hook(this);
    AddObject(exitButton);
}

void MainMenuIU::Callback(int eventNo)
{
    cout << "Event No: " << eventNo << endl;
    if (eventNo == -1) ExitGame();
}

void MainMenuIU::ExitGame()
{
    exit(0);
}

void MainMenuIU::onMouseClickEvent(sf::Vector2i mousePosition)
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

void MainMenuIU::updateTick()
{

}
