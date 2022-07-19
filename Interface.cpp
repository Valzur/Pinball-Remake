#include "Interface.h"
using namespace Valzuroid::Pinball;

Interface::Interface()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  // Remove this line if the game was too laggy
    window.create(sf::VideoMode(WINDOW_WIDTH, GAME_HEIGHT), "Pinball", sf::Style::Titlebar, settings);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(FPSLimit);
}

void Interface::drawLogo(float progress)
{
    //Assuming progres is a value from 1 to 0
    if (progress == 1) 
    {
        //Logo
        if (!LogoTexture.loadFromFile("Assets/Light bg LOGO.png")) {
            cout << "Can't load Logo sprite! " << endl;
        }
        else {
            LogoSprite.setTexture(LogoTexture);
        }
    }

    LogoSprite.setOrigin(LogoSprite.getTexture()->getSize().x / 2.0, LogoSprite.getTexture()->getSize().y / 2.0);
    LogoSprite.setPosition(WINDOW_WIDTH / 2.0, GAME_HEIGHT / 2.0);
    LogoSprite.setColor(sf::Color( 255, 255, 255, progress * 255));
    //LogoSprite.setScale(0.01, 0.01);
    window.draw(LogoSprite);
}

void Interface::getControls(bool & exit, bool & left, bool & right, bool & space)
{
    sf::Event event;
    while (window.pollEvent(event));
    space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    exit = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

void Interface::clear()
{
    window.clear(backgroundColor);
}

void Interface::display()
{
    window.display();
}

void Interface::drawFPS() {
    text.setString(FPS);
    text.setCharacterSize(24);
    text.setFillColor(textColor);
    text.setPosition(0,0);
    window.draw(text);
}

void Interface::setFPS(string fps) 
{
    FPS = fps;
}

void Interface::drawText(string Text, int FontSize, Vector2D position) 
{

    text.setFont(font);
    text.setString(Text);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setCharacterSize(FontSize);
    text.setFillColor(textColor);
    text.setOrigin(bounds.left + bounds.width / 2.0, bounds.top + bounds.height / 2.0);
    text.setPosition(position.x, position.y);
    window.draw(text);
}

void Interface::LoadGraphics() {
    //Load Fonts
    if(!font.loadFromFile("Assets/Fonts/xirod.ttf")){
        cout<< "Can't load font! "<< endl;
    }else{
        FPSText.setFont(font);
    }
}

void Interface::drawBackground()
{
    sf::RectangleShape Background(sf::Vector2f(GAME_WIDTH,GAME_HEIGHT));
    Background.setFillColor(backgroundColor);
    window.draw(Background);
}

void Interface::drawUIBackground() {
    sf::RectangleShape Box(sf::Vector2f(WINDOW_WIDTH-GAME_WIDTH,GAME_HEIGHT));

    Box.setOrigin(0,0);
    Box.setPosition(GAME_WIDTH,0);
    Box.setFillColor(sf::Color(54,79,107));

    window.draw(Box);
}

sf::RenderWindow &Interface::GetWindow() {
    return window;
}
