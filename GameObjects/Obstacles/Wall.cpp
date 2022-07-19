#include "Wall.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

Wall::Wall(bool isVertical, Vector2D Center):Center(Center),isVertical(isVertical){
    if(buffer.loadFromFile("Assets/SFX/WallHit.wav")){
        sound.setBuffer(buffer);
    }else{
        std:: cout << "Unable to load Wallhit.wav!" << std::endl;
    }
}

void Wall::draw(Interface &interface){
    if (isVertical) {
        sf::RectangleShape Wall({ GlobalWidth,GAME_HEIGHT });

        //Origin
        Wall.setOrigin({ GlobalWidth / 2.0,GAME_HEIGHT / 2.0 });

        //Aesthetics
        Wall.setFillColor(color);

        //Position
        Wall.setPosition(Center);

        interface.GetWindow().draw(Wall);
    }
    else {
        sf::RectangleShape Wall({ GAME_WIDTH,GlobalWidth });

        //Origin
        Wall.setOrigin({ GAME_WIDTH / 2.0,GlobalWidth / 2.0 });

        //Aesthetics
        Wall.setFillColor(color);

        //Position
        Wall.setPosition(Center);

        interface.GetWindow().draw(Wall);
    }
}

CollisionResponse Wall::collideWith(Ball &ball, double collision_time, GameManager &manager)
{
    if(isVertical) {
        if (!collidedLastFrame && abs(Center.x - ball.GetCenter().x) < ball.GetRadius()) {
            collidedLastFrame = true;
            ball.setVelocity({-ball.getVelocity().x,ball.getVelocity().y});
            sound.play();
            return Vector2D{ 0.00001, 0.0001 };
        } else {
            collidedLastFrame = false;
        }
    }else{
        if (!collidedLastFrame && abs(Center.y - ball.GetCenter().y) < ball.GetRadius()) {
            collidedLastFrame = true;
            ball.setVelocity({ball.getVelocity().x,-ball.getVelocity().y});
            sound.play();
            return Vector2D{ 0.00001, 0.0001 };
        } else {
            collidedLastFrame = false;
        }
    }
    return Vector2D::zero;
}
