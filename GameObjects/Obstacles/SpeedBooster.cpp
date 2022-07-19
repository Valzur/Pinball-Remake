#include "SpeedBooster.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

void SpeedBooster::draw(Interface &interface) 
{
    sf::CircleShape SpeedBooster(radius);
    if (Hit) {
        SpeedBooster.setFillColor(sf::Color(254, 255, 137));
    }
    else {
        SpeedBooster.setFillColor(sf::Color::Transparent);
    }
    SpeedBooster.setOrigin(radius, radius);
    SpeedBooster.setPosition(Center.x, Center.y);
    SpeedBooster.setOutlineThickness(outlineThickness);
    SpeedBooster.setOutlineColor(outlineColor);
    interface.GetWindow().draw(SpeedBooster);

    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
    sprite.setPosition(Center.x, Center.y);
    sprite.setScale(0.07, 0.07);
    interface.GetWindow().draw(sprite);
}

CollisionResponse SpeedBooster::collideWith(Ball &ball, double collision_time, GameManager&manager) {
    bool isInside = BICCollision(ball,Center,radius);

    if(isInside){
        ball.Boost(SpeedBoosterAmount);
        Hit = true;
        HitTimer=FlashTimer;
    }
    if( (HitTimer>0) & Hit ){
        HitTimer-=collision_time;
    }else{
        Hit = false;
    }
    return Vector2D{0,0};
}

void SpeedBooster::start()
{
    //SpeedBooster
    if (!texture.loadFromFile("Assets/Sprites/SpeedBooster.png")) {
        cout << "Can't load SpeedBooster sprite! " << endl;
    }
    else {
        sprite.setTexture(texture);
    }
}

SpeedBooster::SpeedBooster(double radius, Vector2D Center): Center(Center) {
    this->radius=radius;
}
