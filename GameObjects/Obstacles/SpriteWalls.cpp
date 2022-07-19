#include "SpriteWalls.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

void SpriteWalls::LoadTexture(string path) {
    if (!texture.loadFromFile(path)){
    cout<<"Error, Couldn't load texture.."<<endl;
    }else{
        sprite.setTexture(texture);
    }
}

void SpriteWalls::SetPosition(Vector2D pos) {
    sprite.setPosition(pos.x,pos.y);
}

sf::Sprite SpriteWalls::GetSprite() {
    return sprite;
}

CollisionResponse SpriteWalls::collideWith(Ball& ball, double collision_time, GameManager& manager)
{
    return Vector2D();
}

SpriteWalls::SpriteWalls(string TexturePath, Vector2D SpritePosition) {
    if (!texture.loadFromFile(TexturePath)){
        cout<<"Error, Couldn't load texture.."<<endl;
    }else{
        sprite.setTexture(texture);
        sprite.setPosition(SpritePosition.x,SpritePosition.y);
        sprite.setColor(sf::Color::Black);
    }
}

void SpriteWalls::draw(Interface& interface)
{

}

