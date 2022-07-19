#include"ScoreMultiplier.h"
using namespace std;
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

ScoreMultiplier::ScoreMultiplier(Vector2D pos, double rad) : Bumper(pos, rad, SCOREM) {
	setScorepoints(0);
	Center=pos;
	Radius=rad;
    
}
	
CollisionResponse ScoreMultiplier::collideWith(Ball & ball, double collision_time, GameManager& manager){
    Vector2D Acceleration = CircleCollision(ball,Center,Radius,collision_time);

    if(Acceleration==Vector2D{0,0}){
        if(Hit &(hitTimer>0))
            hitTimer-=collision_time;
        else {
            hitTimer=FlashTimer;
            Hit=false;
        }
    }else{
        Hit=true;
        manager.addScore(400);
        manager.MultiplyScore(1.5);
        sound.play();
        ball.setVelocity(Acceleration*collision_time);
    }

    return Vector2D::zero;
}

void ScoreMultiplier::start()
{
    if (buffer.loadFromFile("Assets/SFX/ScoreMultiplier.wav")) {
        sound.setBuffer(buffer);
    }
    else {
        std::cout << "Unable to load ScoreMultiplier.wav!" << std::endl;
    }

    //Thrust
    if (!texture.loadFromFile("Assets/Sprites/ScoreMultiplier.png")) {
        cout << "Can't load ScoreMultiplier sprite! " << endl;
    }
    else {
        sprite.setTexture(texture);
    }
}

void ScoreMultiplier::draw(Interface& interface) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setOutlineThickness(1.5 * outlineThickness);
    circle.setOutlineColor(outlineColor);

    circle.setPosition(position.x, position.y);
    if (Hit) {
        circle.setFillColor(hitColor);
    }
    else {
        circle.setFillColor(color);
    }
    interface.GetWindow().draw(circle);
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
    sprite.setPosition(position);
    sprite.setScale(0.2, 0.2);
    interface.GetWindow().draw(sprite);
}