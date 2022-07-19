#include "Collectable.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

Collectable::Collectable(double radius, string L,Vector2D Center): Center(Center) {
    this->radius=radius;
    this->L=L;
    if(buffer.loadFromFile("Assets/SFX/StarCollect.wav")){
        sound.setBuffer(buffer);
    }else{
        std:: cout << "Unable to load StarCollect.wav!" << std::endl;
    }
}

void Collectable::draw(Interface &interface)
{
    if (!Active) return;

    sf::CircleShape Collectable(radius);
    if (Used) {
        Collectable.setFillColor(radiantColor);
    }
    else {
        Collectable.setFillColor(sf::Color::Transparent);
    }
    interface.drawText(L, 24, { Center.x, Center.y });
    Collectable.setOrigin(radius, radius);
    Collectable.setPosition(Center.x, Center.y);
    Collectable.setOutlineThickness(2);
    Collectable.setOutlineColor(radiantColor);
    interface.GetWindow().draw(Collectable);
}

CollisionResponse Collectable::collideWith(Ball &ball, double collision_time, GameManager &manager)
{
    if(Used){
        if(Timer>0){
            Timer-=collision_time;
        } else {
            if(Active){
                Active=false;
                sound.play();
                manager.addScore(5000);
            }
        }

    } else {
        if(BICCollision(ball,Center,radius)){
            Used=true;
        }
    }
    return Vector2D::zero;
}

