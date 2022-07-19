#include "Ramp.h"
using namespace Valzuroid::Pinball::GameObjects::Obstacles;
using namespace Valzuroid::Pinball;

void Ramp::draw(Interface &interface) {
    sf::RectangleShape Wall(Size);

    //Aesthetics
    Wall.setFillColor(color);

    //Orientation
    Wall.setOrigin(0, Size.y / 2.0);
    Wall.setPosition(Center);
    Wall.setRotation(Angle);

    interface.GetWindow().draw(Wall);
}


CollisionResponse Ramp::collideWith(Ball &ball, double collision_time, GameManager &manager) {

    //cout << "Angle: " << Angle << ", Xposition: " << Center.x << ", Yposition: " << Center.y << endl;

    CircleLineCollision(ball, Center, Center + Vector2D{cos(Angle), sin(Angle)} * Size.y );
       

    return Vector2D::zero;
}

void Ramp::start()
{
    if (buffer.loadFromFile("Assets/SFX/WallHit.wav")) {
        sound.setBuffer(buffer);
    }
    else {
        std::cout << "Unable to load Wallhit.wav!" << std::endl;
    }
}

Ramp::Ramp(Vector2D Size, Vector2D Center, double Angle):Size(Size),Center(Center),Angle(Angle) {
    
    this->Size={Size.x,GlobalWidth/2.0};
}
