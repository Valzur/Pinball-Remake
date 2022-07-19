#include "Ball.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects;

Ball::Ball(Vector2D center,float radius, Vector2D velocity,bool Main): initialPosition(center), velocity(velocity),initialVelocity(velocity),radius(radius) {
    isActive=false;
    isMain=Main;
    setCenter(initialPosition);
    if(!Main){
        if(buffer.loadFromFile("Assets/SFX/Captive.wav")){
            sound.setBuffer(buffer);
        }else{
            std:: cout << "Unable to load Captive.wav!" << std::endl;
        }
    }
}

float Ball::GetRadius() const
{
    return radius;
}

Vector2D Ball::GetCenter() const
{
    return center;
}

Vector2D Ball::getVelocity() const
{
    return velocity;
}

void Ball::move(double time, GameManager& manager,bool &lost){
    if(isActive){
        if(!isUsedLane) {
            manager.ValueUpdate(*this,lost);
            // Kinematic equations for planar motion of a particle
            setVelocity(velocity + acceleration * time );
            setCenter( center + velocity *speedBoost* time + acceleration * time * time * 0.5 );
        } else {
            if(isDirectedUp){
                if(laneLength>0){
                    velocity=Vector2D{0,-1}*VectorNorm(velocity);
                    center+=velocity*time*speedBoost;
                    laneLength-=VectorNorm(velocity)*time*speedBoost;
                }else{
                    isUsedLane=false;
                }
            }else{
                if(laneLength>0){
                    velocity=Vector2D{0,1}*VectorNorm(velocity);
                    center+=velocity*time*speedBoost;
                    laneLength-=VectorNorm(velocity)*time*speedBoost;
                }else{
                    isUsedLane=false;
                }
            }
        }
    }
}

void Ball::start()
{
    //Loading Ball sprite
    if (!Balltexture.loadFromFile("Assets/Sprites/pokeball.png")) {
        // error...
        cout << "Error loading pokeball!" << endl;
    }
    else {
        Ballsprite.setTexture(Balltexture);
    }
}

void Ball::draw (Interface & interface)
{
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setOutlineThickness(outlineThickness);
    circle.setOutlineColor(outlineColor);
    circle.setFillColor(ballFillColor);
    circle.setPosition(center.x, center.y);
    interface.GetWindow().draw(circle);

    //Graphics b2a w kda
    Ballsprite.setTexture(Balltexture);
    Ballsprite.setOrigin(Ballsprite.getTexture()->getSize().x / 2.0, Ballsprite.getTexture()->getSize().y / 2.0);
    Ballsprite.setPosition(center.x, center.y);
    Ballsprite.setScale(0.01, 0.01);
    interface.GetWindow().draw(Ballsprite);
}

void Ball::setCenter(Vector2D pos) {
    bool Check1 = pos.x < radius,
    Check2 = pos.x > GAME_WIDTH - radius,
    Check3 = pos.y < radius;
    Vector2D ModifiedPosition = pos;
    if(Check1)
        ModifiedPosition = { radius , pos.y };

    if(Check2)
        ModifiedPosition = { GAME_WIDTH - radius, pos.y };

    if(Check3)
        ModifiedPosition = { pos.x, radius };

    center = ModifiedPosition;
}

void Ball::setVelocity(Vector2D vel) {
    if(VectorNorm(vel) < 600){
        velocity = vel;
    } else {
        velocity = vel * VelocityControl / VectorNorm(vel);
    }
}

void Ball::Activate(bool & space) {
    if(space & isMain){
        isActive=true;
    }
}

void Ball::deActivate() {
    isActive=false;
    isUsedPortal=false;
    isUsedLane=false;
}

Vector2D Ball::collideWith(Ball &ball, float collision_time, GameManager & manager) {
    if(ball.GetCenter().x==center.x & ball.GetCenter().y == center.y){
        return {0,0};
    }else {
        Vector2D acc = {0, 0};
        Vector2D dir;
        if (VectorDistance(ball.GetCenter(), center) <= radius + ball.GetRadius()) {
            //Break Captivity
            if (!isMain & !isActive){
                isActive=true;
                sound.play();
            }

            //Readjust balls
            dir = VectorDirection(center, ball.GetCenter());
            setCenter(center + dir * VectorNorm(center - ball.GetCenter()));
            //Acceleration measurement
            acc = ball.getVelocity();
        }
        return acc;
    }
}

void Ball::Reset() {
    deActivate();
    if(isMain){
        setCenter(initialPosition);
        setVelocity(initialVelocity);
    }
}

bool Ball::getisMain() const {
    return isMain;
}

bool Ball::getIsUsedPortal() const{
    return isUsedPortal;
}

void Ball::setUsedPortal(bool Used) {
    isUsedPortal=Used;
}

Vector2D Ball::getAcceleration() const {
    return  acceleration;
}

void Ball::setAcceleration(Vector2D Acceleration) {
    this-> acceleration=Acceleration;
}

void Ball::Boost(double BoostValue) {
    boostTimer=boostDuration;
    speedBoost=BoostValue;
}

void Ball::UpdateBoost(double time) {
    if(boostTimer>0){
        boostTimer-=time;
    }
}

void Ball::SetLaneLength(double Length) {
    this->laneLength=Length;
}

void Ball::SetLaneMode(bool Active) {
    isUsedLane=Active;
}

bool Ball::GetLaneMode()const{
    return isUsedLane;
}

void Ball::SetLaneDirection(bool isUp) {
    isDirectedUp=isUp;
}
