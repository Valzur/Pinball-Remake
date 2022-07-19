#include"ThrustBumper.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

ThrustBumper::ThrustBumper(Vector2D pos, double rad) : Bumper(pos, rad, BumperType::THRUST) {
    
}

void ThrustBumper::draw(Interface& interface) {
    sf::CircleShape circle(radius);
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
    sprite.setPosition(position.x, position.y);
    sprite.setScale(0.015, 0.015);

    circle.setOrigin(radius, radius);
    circle.setPosition(position);
    if (Hit) {
        circle.setFillColor(hitColor);
    }
    else {
        circle.setFillColor(fillColor);
    }
    circle.setOutlineThickness(1.5 * outlineThickness);
    circle.setOutlineColor(outlineColor);

    interface.GetWindow().draw(circle);
    interface.GetWindow().draw(sprite);
}

CollisionResponse ThrustBumper::collideWith(Ball& ball, double collision_time, GameManager& manager) {
    Vector2D Acceleration = { 0,0 };
    Acceleration = CircleCollision(ball, position, radius, collision_time);
    if(Acceleration==Vector2D{0,0}){
        if(Hit &(hitTimer>0))
            hitTimer-=collision_time;
        else {
            hitTimer=FlashTimer;
            Hit=false;
            AllowHit=true;
        }
    }else{
        Hit=true;
        if(AllowHit){
            ball.setVelocity(Acceleration*ThrustBumperBoost/collision_time);
            sound.play();
            manager.addScore(750);
            AllowHit=false;
        }
    }
    return Vector2D::zero;
}

void ThrustBumper::start()
{
    if (buffer.loadFromFile("Assets/SFX/Thrust.wav")) {
        sound.setBuffer(buffer);
    }
    else {
        std::cout << "Unable to load Thrust.wav!" << std::endl;
    }

    //Thrust
    if (!texture.loadFromFile("Assets/Sprites/Thurst.png")) {
        cout << "Can't load ThrustBumper sprite! " << endl;
    }
    else {
        sprite.setTexture(texture);
    }
}
