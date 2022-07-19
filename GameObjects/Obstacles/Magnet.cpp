#include "Magnet.h"

using namespace Valzuroid::Pinball::GameObjects::Obstacles;
using namespace Valzuroid::Pinball;

Magnet::Magnet(Vector2D Position, double magnetRadius, double radius):Position(Position),magnetRadius(magnetRadius),radius(radius) {
}

void Magnet::draw(Interface &interface) {
    sf::CircleShape magnet(magnetRadius);
    magnet.setOrigin(magnetRadius, magnetRadius);
    magnet.setOutlineThickness(outlineThickness);
    magnet.setFillColor(sf::Color(7, 26, 82, 80));

    magnet.setPosition(Position.x, Position.y);
    interface.GetWindow().draw(magnet);

    //Sprite
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
    sprite.setPosition(Position.x, Position.y);
    sprite.setScale(0.07, 0.07);
    sprite.setColor(sf::Color(255, 255, 255, 128));
    interface.GetWindow().draw(sprite);
}

CollisionResponse Magnet::collideWith(Ball &ball, double collision_time, GameManager &manager) {
    Vector2D Acceleration = { 0,0 },farD;
    double ScalarVelocity = VectorNorm(ball.getVelocity());
    farD = VectorDirection( ball.GetCenter(),Position);
    if (VectorDistance(ball.GetCenter(), Position) <= ball.GetRadius() + magnetRadius) {
        Acceleration = farD * ScalarVelocity * MagnetForce;
        sound.play();
    }

    return Acceleration;
}

void Magnet::start()
{
    if (!texture.loadFromFile("Assets/Sprites/Magnet.png")) {
        cout << "Error, unable to load Magnet texture!" << endl;
    }
    else {
        sprite.setTexture(texture);
    }
    if (buffer.loadFromFile("Assets/SFX/Magnet.wav")) {
        sound.setBuffer(buffer);
    }
    else {
        std::cout << "Unable to load Magnet.wav!" << std::endl;
    }
}

double Magnet::getMagnetRadius() const {
    return magnetRadius;
}

double Magnet::getRadius() const {
    return radius;
}

Vector2D Magnet::getCenter() const {
    return Position;
}

void Magnet::setMagnetRadius(double magnetRadius) {
    magnetRadius=magnetRadius;
}

void Magnet::setRadius(double radius) {
    this->radius=radius;
}
