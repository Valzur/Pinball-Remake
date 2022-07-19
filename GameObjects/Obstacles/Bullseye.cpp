#include "Bullseye.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

Bullseye::Bullseye(Vector2D Center, double Length, bool isVertical):Center(Center), Length(Length),isVertical(isVertical) {}

void Bullseye::draw(Interface &interface) {

    if (isVertical) {
        sf::RectangleShape Ace(Vector2D{ width, Length / 3.0 }),
            Expert(Vector2D{ width, Length * 2.0 / 3.0 }),
            Novice(Vector2D{ width, Length });
        //Origin
        Ace.setOrigin(width / 2.0, Length / 6.0);
        Expert.setOrigin(width / 2.0, Length / 3.0);
        Novice.setOrigin(width / 2.0, Length / 2.0);

        //Positioning
        Ace.setPosition(Center);
        Expert.setPosition(Center);
        Novice.setPosition(Center);

        //Aesthetics
        Ace.setFillColor(sf::Color(254, 255, 137));
        Expert.setFillColor(sf::Color(255, 159, 104));
        Novice.setFillColor(sf::Color(248, 89, 89));

        //Draw
        interface.GetWindow().draw(Novice);
        interface.GetWindow().draw(Expert);
        interface.GetWindow().draw(Ace);
    }
    else {
        sf::RectangleShape Ace(Vector2D{ Length / 3.0, width }),
            Expert(Vector2D{ Length * 2 / 3.0, width }),
            Novice(Vector2D{ Length, width });
        //Origin
        Ace.setOrigin(Length / 6.0, width / 2.0);
        Expert.setOrigin(Length / 3.0, width / 2.0);
        Novice.setOrigin(Length / 2.0, width / 2.0);

        //Positioning
        Ace.setPosition(Center);
        Expert.setPosition(Center);
        Novice.setPosition(Center);

        //Aesthetics
        Ace.setFillColor(sf::Color(254, 255, 137));
        Expert.setFillColor(sf::Color(255, 159, 104));
        Novice.setFillColor(sf::Color(248, 89, 89));

        //Draw
        interface.GetWindow().draw(Novice);
        interface.GetWindow().draw(Expert);
        interface.GetWindow().draw(Ace);
    }
}

CollisionResponse Bullseye::collideWith(Ball &ball, double collision_time, GameManager &manager) {
    if(isVertical){

    }else {
        if ( ball.GetCenter().y - Center.y < ball.GetRadius() + width ) {
            if ((ball.GetCenter().x > Center.x - Length / 6.0) & (ball.GetCenter().x > Center.x + Length / 6.0)) {
                //Ace position
                if(!collidedLastFrame){
                    //manager.addScore(2500);
                    collidedLastFrame = true;
                }
            } else if ((ball.GetCenter().x > Center.x - Length / 3.0) & (ball.GetCenter().x > Length / 3.0)) {
                //Expert position
                if(!collidedLastFrame){
                    //manager.addScore(1000);
                    collidedLastFrame = true;
                }
            } else if ((ball.GetCenter().x > Center.x - Length / 2.0) & (ball.GetCenter().x > Length / 2.0)) {
                //Novice Position
                if(!collidedLastFrame){
                    //manager.addScore(500);
                    collidedLastFrame = true;
                }
            }else{
                collidedLastFrame = false;
            }
        }else{
            collidedLastFrame = false;
        }
    }
    return Vector2D{0,0};
}
