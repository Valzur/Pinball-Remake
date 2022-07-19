#include "Flipper.h"
using namespace Valzuroid::Pinball::GameObjects;

Flipper::Flipper(FlipperType type, Vector2D center, double length, double angle, double majorRadius, double minorRadius, double NormalAngle, double ExtendedAngle,double Velocity):
    type(type), center(center), length(length), angle(angle), majorRadius(majorRadius), minorRadius(minorRadius),NormalAngle(NormalAngle),ExtendedAngle(ExtendedAngle), Velocity(Velocity){
    if(buffer.loadFromFile("Assets/SFX/Flipper.wav")){
        sound.setBuffer(buffer);
    }else{
        std:: cout << "Unable to load Flipper.wav!" << std::endl;
    }
}

CollisionResponse Flipper::collideWith(Ball & ball, double collision_time, GameManager & manager)
{
    Vector2D velocity={0,0}, Direction;
    Direction =  Vector2D {cos(angle*180/PI),sin(angle*180/PI)}*length;

    velocity = RectangleCollision(ball,length,minorRadius,angle,center);
    if(velocity != Vector2D{0,0}){
        ball.setVelocity(velocity*-impulseMultiplier);
    }
    return Vector2D::zero;
}

void Flipper::draw(Interface & interface)
{
    double flip = type == LEFT ? 1.0f : -1.0f;

    // Draw the major circle outline
    sf::CircleShape majorCircleOutline(majorRadius);
    majorCircleOutline.setOutlineThickness(outlineThickness);
    majorCircleOutline.setOutlineColor(outlineColor);
    majorCircleOutline.setFillColor(flipperFillColor);
    majorCircleOutline.setOrigin(majorRadius, majorRadius);
    majorCircleOutline.setPosition(center.x, center.y);
    interface.GetWindow().draw(majorCircleOutline);

    // Draw the minor circle outline
    sf::CircleShape minorCircleOutline(minorRadius);
    minorCircleOutline.setOutlineThickness(outlineThickness);
    minorCircleOutline.setOutlineColor(outlineColor);
    minorCircleOutline.setFillColor(flipperFillColor);
    minorCircleOutline.setOrigin(minorRadius - length, minorRadius);
    minorCircleOutline.setPosition(center.x, center.y);
    minorCircleOutline.rotate(angle);
    minorCircleOutline.setScale(flip, 1.0f);
    interface.GetWindow().draw(minorCircleOutline);

    // Draw the convex shape connecting the two circles
    sf::ConvexShape convexBody(4);
    convexBody.setPoint(0, sf::Vector2f(0, -outlineThickness));
    convexBody.setPoint(1, sf::Vector2f(0, 2 * majorRadius + outlineThickness));
    convexBody.setPoint(2, sf::Vector2f(length, majorRadius + minorRadius + outlineThickness));
    convexBody.setPoint(3, sf::Vector2f(length, majorRadius - minorRadius - outlineThickness));
    convexBody.setFillColor(flipperFillColor);
    convexBody.setOrigin(0, majorRadius);
    convexBody.setPosition(center.x, center.y);
    convexBody.setRotation(angle);
    convexBody.setScale(flip, 1.0f);
    interface.GetWindow().draw(convexBody);

    // Draw the inside circle
    sf::CircleShape insideCircle(minorRadius);
    insideCircle.setFillColor(outlineColor);
    insideCircle.setOrigin(minorRadius, minorRadius);
    insideCircle.setPosition(center.x, center.y);
    interface.GetWindow().draw(insideCircle);

    // Draw the top line
    sf::ConvexShape topLine(4);
    topLine.setPoint(0, sf::Vector2f(0, -outlineThickness));
    topLine.setPoint(1, sf::Vector2f(0, 0));
    topLine.setPoint(2, sf::Vector2f(length, majorRadius - minorRadius));
    topLine.setPoint(3, sf::Vector2f(length, majorRadius - minorRadius - outlineThickness));
    topLine.setFillColor(outlineColor);
    topLine.setOrigin(0, majorRadius);
    topLine.setPosition(center.x, center.y);
    topLine.setRotation(angle);
    topLine.setScale(flip, 1.0f);
    interface.GetWindow().draw(topLine);

    // Draw the bottom line
    sf::ConvexShape bottomLine(4);
    bottomLine.setPoint(0, sf::Vector2f(0, 2 * majorRadius));
    bottomLine.setPoint(1, sf::Vector2f(0, 2 * majorRadius + outlineThickness));
    bottomLine.setPoint(2, sf::Vector2f(length, majorRadius + minorRadius + outlineThickness));
    bottomLine.setPoint(3, sf::Vector2f(length, majorRadius + minorRadius));
    bottomLine.setFillColor(outlineColor);
    bottomLine.setOrigin(0, majorRadius);
    bottomLine.setPosition(center.x, center.y);
    bottomLine.setRotation(angle);
    bottomLine.setScale(flip, 1.0f);
    interface.GetWindow().draw(bottomLine);
}

void Flipper::RotateFlipper(double a, double time){
    if(a>0){
        if(angle<0.7*a) {
            angle += time * Velocity;
            impulseMultiplier=1.5;
        }else if(angle>a/0.7){
            angle -= time * Velocity;
            impulseMultiplier=1.5;
        }else{
            angle=a;
            impulseMultiplier=1;
        }
    }else{
        if(angle<a/0.7) {
            angle += time * Velocity;
            impulseMultiplier=1.5;
        }else if(angle>a*0.7){
            angle -= time * Velocity;
            impulseMultiplier=1.5;
        }else{
            angle=a;
            impulseMultiplier=1;
        }
    }

}

void Flipper::MoveFlipper(bool left, bool right, double delta_time) {
    //A little finicky, but its cleaner :')
    if(!left & left){
        sound.play();
    }
    if(!right & right){
        sound.play();
    }

    switch(type) {
        //Left
        //If clicked
        case FlipperType(LEFT):
            if (left) {
                RotateFlipper(-ExtendedAngle, delta_time);
            } else {
                RotateFlipper(-NormalAngle, delta_time);
            }
            break;
        case FlipperType(RIGHT):
            if (right) {
                RotateFlipper(ExtendedAngle, delta_time);
            } else {
                RotateFlipper(NormalAngle, delta_time);
            }
            break;
    }
    left = left;
    right = right;
}
