#include "Lane.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

Lane::Lane(double Length, Vector2D Center, double Width):width(Width), length(Length),Center(Center) {}

void Lane::SetLength(double Length){
this->length=Length;
}

void Lane::SetCenter(Vector2D Center) {
this->Center=Center;
}

double Lane::GetLength() const {
    return length;
}

Vector2D Lane::GetCenter() const {
    return Center;
}

void Lane::draw(Interface &interface) {
    //Initializing
    sf::RectangleShape LeftLine(sf::Vector2f(5, length)), RightLine(sf::Vector2f(5, length));
    //Aesthetics
    LeftLine.setFillColor(outlineColor);
    RightLine.setFillColor(outlineColor);

    //Positioning
    LeftLine.setOrigin(2.5, length / 2.0);
    RightLine.setOrigin(2.5, length / 2.0);
    LeftLine.setPosition(Center.x - width, Center.y);
    RightLine.setPosition(Center.x + width, Center.y);

    //Drawing
    interface.GetWindow().draw(LeftLine);
    interface.GetWindow().draw(RightLine);
}

CollisionResponse Lane::collideWith(Ball &ball, double collision_time, GameManager &manager) {
        Top = BICCollision(ball,Vector2D {Center.x,Center.y-length/2.0},width);
        Bottom = BICCollision(ball,Vector2D {Center.x,Center.y+length/2.0},width);

    if(Top & Bottom){
        bool Check1 = BICCollision(ball,Vector2D {Center.x,Center.y-length/2.0},width),
        Check2 = BICCollision(ball,Vector2D {Center.x,Center.y+length/2.0},width);
        if(!Check1 & !Check2){
            ball.SetLaneMode(false);
        }
    } else if (Bottom & !ball.GetLaneMode()){
        ball.setCenter(Vector2D {Center.x,Center.y+length/2.0});
        ball.SetLaneMode(true);
        ball.SetLaneDirection(true);
        ball.SetLaneLength(length+width);
    } else if (Top & !ball.GetLaneMode()){
        ball.setCenter(Vector2D {Center.x,Center.y-length/2.0});
        ball.SetLaneMode(true);
        ball.SetLaneDirection(false);
        ball.SetLaneLength(length+width);
    }

    return Vector2D::zero;
}
