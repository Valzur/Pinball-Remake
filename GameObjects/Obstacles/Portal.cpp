#include "Portal.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

void Portal::draw(Interface &interface) {
    sf::CircleShape circle1(radius), circle2(radius);
    circle1.setOrigin(radius, radius);
    circle1.setOutlineThickness(outlineThickness);
    circle1.setOutlineColor(color);
    circle1.setFillColor(sf::Color::Transparent);

    circle2.setFillColor(sf::Color::Transparent);
    circle2.setOrigin(radius, radius);
    circle2.setOutlineThickness(outlineThickness);
    circle2.setOutlineColor(color);

    circle1.setPosition(Pos1.x, Pos1.y);
    circle2.setPosition(Pos2.x, Pos2.y);
    interface.GetWindow().draw(circle2);
    interface.GetWindow().draw(circle1);

    //Sprite
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
    sprite.setPosition(Pos1.x, Pos1.y);
    sprite.setScale(0.1, 0.1);

    interface.GetWindow().draw(sprite);

    sprite.setPosition(Pos2.x, Pos2.y);
    interface.GetWindow().draw(sprite);
    
}

Portal::Portal(Vector2D Pos1, Vector2D Pos2, double radius): Pos1(Pos1), Pos2(Pos2), radius(radius) {}

CollisionResponse Portal::collideWith(Ball &ball, double collision_time, GameManager &manager) {
    bool Portal1,Portal2;
    Portal1=BICCollision(ball,Pos1,radius);
    Portal2=BICCollision(ball,Pos2,radius);
    if(Portal1){
        if(!ball.getIsUsedPortal()){
            ball.setCenter(Pos2);
            ball.setUsedPortal(true);
            sound.play();
        }
    }else if(Portal2){
        if(!ball.getIsUsedPortal()){
            ball.setCenter(Pos1);
            ball.setUsedPortal(true);
            sound.play();
        }
    }else{
        ball.setUsedPortal(false);
    }
    return Vector2D{0,0};
}

void Portal::start()
{
    if (buffer.loadFromFile("Assets/SFX/Portal.wav")) {
        sound.setBuffer(buffer);
    }
    else {
        std::cout << "Unable to load Portall.wav!" << std::endl;
    }

    //Portal Sprite
    if (!texture.loadFromFile("Assets/Sprites/Portal.png")) {
        cout << "Can't load Portal sprite! " << endl;
    }
    else {
        sprite.setTexture(texture);
    }

}

