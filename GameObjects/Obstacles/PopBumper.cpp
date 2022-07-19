#include "PopBumper.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

PopBumper::PopBumper(Vector2D pos, double rad) : Bumper(pos, rad,POP) {
    
}

void PopBumper::draw(Interface &interface) {

    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setOutlineThickness(1.5 * outlineThickness);
    circle.setOutlineColor(outlineColor);

    circle.setPosition(position.x, position.y);
    if (!Hit) {
        circle.setFillColor(hitColor);
    }
    else {
        circle.setFillColor(fillColor);
    }
    interface.GetWindow().draw(circle);
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
    sprite.setPosition(position.x, position.y);
    sprite.setScale(2, 2);
    interface.GetWindow().draw(sprite);
}

CollisionResponse PopBumper::collideWith(Ball &ball, double collision_time, GameManager &manager) {
    Vector2D Acceleration={0,0};
    if(AllowHit)
        Acceleration = CircleCollision(ball, position, radius, collision_time);

    if(Acceleration==Vector2D{0,0}){
        AllowHit = true;
    }else{
        ball.setVelocity(Acceleration*collision_time);
        Hit = true;
        AllowHit = false;
    }

    if(Hit &(hitTimer>0))
        hitTimer-=collision_time;
    else {
        if(hitTimer<=0){
            manager.addScore(400);
            sound.play();
        }

        hitTimer=FlashTimer;
        Hit=false;
    }
    return Vector2D::zero;
}

void PopBumper::start()
{
    if (buffer.loadFromFile("Assets/SFX/Bumper.wav")) {
        sound.setBuffer(buffer);
    }
    else {
        std::cout << "Unable to load Bumper.wav!" << std::endl;
    }

    //Loading Bumper sprite
    if (!texture.loadFromFile("Assets/Sprites/PokeBumper.png")) {
        cout << "Error loading Bumper sprite!" << endl;
    }
    else {
        sprite.setTexture(texture);
    }
}
