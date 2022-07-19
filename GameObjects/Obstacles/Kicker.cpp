#include "Kicker.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

//Note that you just need one file to read both boasters
void Kicker::draw(Interface &interface) {
    //Right
    sf::ConvexShape rKicker; //غير اسم البتاعة ديه ل Kicker
    rKicker.setPointCount(3);
    rKicker.setPoint(0, sf::Vector2f(GAME_WIDTH - 30 - 25, 735.0));
    rKicker.setPoint(1, sf::Vector2f(GAME_WIDTH - 30 - 130, 850));
    rKicker.setPoint(2, sf::Vector2f(GAME_WIDTH - 30 - 25, 600));
    rKicker.setFillColor(sf::Color::Cyan);
    interface.GetWindow().draw(rKicker);

    //Left
    sf::ConvexShape lKicker;
    lKicker.setPointCount(3);
    lKicker.setPoint(0, sf::Vector2f(25, 735.0)); //Replace x,y variables by these numbers when loading from the file
    lKicker.setPoint(1, sf::Vector2f(130, 850));
    lKicker.setPoint(2, sf::Vector2f(25, 600));
    lKicker.setFillColor(sf::Color::Cyan);
    interface.GetWindow().draw(lKicker);
}

Kicker::Kicker(double x1, double x2, double x3, double y1, double y2, double y3) {
    this->x1=x1;
    this->x3=x3;
    this->x2=x2;
    this->y1=y1;
    this->y2=y2;
    this->y3=y3;
}

CollisionResponse Kicker::collideWith(Ball &ball, double collision_time, GameManager &manager) {
    return Vector2D{0,0};
}
