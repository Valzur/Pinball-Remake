#include "Switch.h"
#include <cmath>

using namespace std;
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

Switch::Switch(Vector2D Center,double Length) :collidedLastFrame(false), Center(Center),Length(Length) {
    if(buffer.loadFromFile("Assets/SFX/WallHit.wav")){
        sound.setBuffer(buffer);
    }else{
        std:: cout << "Unable to load WallHit.wav!" << std::endl;
    }
}

void Switch::draw(Interface& interface)
{
    sf::RectangleShape line(sf::Vector2f(Length, GlobalWidth));
    line.setOrigin(Length, 5);
    line.setPosition(Center);
    if (Used) {
        line.setFillColor(usedColor);
    }
    else {
        line.setFillColor(unusedColor);
    }
    interface.GetWindow().draw(line);
}

CollisionResponse Switch::collideWith(Ball &ball, double collision_time, GameManager &manager) {
    if(InRange(ball.GetCenter().x,Center.x + Length/2.0,Center.x - Length/2.0)){
        if(InRange(ball.GetCenter().y, Center.y + 5, Center.y - 5)){
            if(Used){
                if(collidedLastFrame){
                    //Nothing
                    collidedLastFrame = false;
                }else{
                    collidedLastFrame = true;
                    ball.setVelocity({ball.getVelocity().x,-ball.getVelocity().y});
                    sound.play();
                }
            }else{
                if(collidedLastFrame){
                    Used = (Direction != ball.getVelocity().y > 0);
                    collidedLastFrame = !Used;
                }else{
                    collidedLastFrame = true;
                    Direction = ball.getVelocity().y > 0;
                }
            }
        }
    }
    return Vector2D{0,0};
}
