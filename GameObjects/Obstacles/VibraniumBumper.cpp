#include "VibraniumBumper.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

VibraniumBumper:: VibraniumBumper(Vector2D pos, double rad): Bumper(pos,rad,  VIBRANIUM){
    
}
void VibraniumBumper::draw(Interface& interface) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);
    circle.setFillColor(sf::Color(8, 105, 114, 255));
    circle.setOutlineThickness(1.3 * outlineThickness);
    circle.setOutlineColor(sf::Color::Black);
    interface.GetWindow().draw(circle);

    //drawing texture for 1st circle
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
    sprite.setPosition(position);
    sprite.setScale(0.4, 0.4);
    sprite.setColor(sf::Color(255, 255, 255, 128));
    interface.GetWindow().draw(sprite);
}

CollisionResponse VibraniumBumper::collideWith(Ball& ball, double collision_time, GameManager& manager) {
    if (ball.GetRadius() + radius >= VectorDistance(ball.GetCenter(), position)) {
        ball.setVelocity({ 0,0 });
        if(SoundDelay <= 0){
            sound.play();
            SoundDelay = VibraniumFlash;
        }
        manager.addScore(-1);
    }
    if(SoundDelay > 0){
        SoundDelay -= collision_time;
    }
    return Vector2D::zero;
}

void VibraniumBumper::start()
{
    //Vibranium
    if (!texture.loadFromFile("Assets/Sprites/Vibranium.png")) {
        cout << "Can't load Vibranium sprite! " << endl;
    }
    else {
        sprite.setTexture(texture);
    }

    if (buffer.loadFromFile("Assets/SFX/Vibranium.wav")) {
        sound.setBuffer(buffer);
    }
    else {
        std::cout << "Unable to load Vibranium.wav!" << std::endl;
    }
}

