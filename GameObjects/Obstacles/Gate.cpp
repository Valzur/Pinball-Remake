#include "Gate.h"
using namespace Valzuroid::Pinball;
using namespace Valzuroid::Pinball::GameObjects;
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

void Gate::draw(Interface &interface) {
    sf::RectangleShape UpperGate(sf::Vector2f(length, width / 2.0)),
        LowerGate(sf::Vector2f(length, width / 2.0));

    //Origin to center
    LowerGate.setOrigin(length / 2.0, width / 4.0);
    UpperGate.setOrigin(length / 2.0, width / 4.0);

    //Coloring
    if (AllowUp) {
        UpperGate.setFillColor(outlineColor);
        LowerGate.setFillColor(radiantColor);
    }
    else {
        UpperGate.setFillColor(radiantColor);
        LowerGate.setFillColor(outlineColor);
    }

    UpperGate.setPosition(center.x, center.y - width / 4.0);
    LowerGate.setPosition(center.x, center.y + width / 4.0);
    interface.GetWindow().draw(UpperGate);
    interface.GetWindow().draw(LowerGate);
}

Gate::Gate(Vector2D Center, double length, double width,bool AllowUp) {
    this->center.x=Center.x;
    this->center.y=Center.y;
    this->length=length;
    this->width=width;
    this->AllowUp=AllowUp;
}

CollisionResponse Gate::collideWith(Ball &ball, double collision_time, GameManager &manager) {
    if( (ball.GetCenter().x > center.x - length/2.0) & ( ball.GetCenter().x < center.x + length/2.0) ){
        //Control parameter for perfectionists :'D
        int Direction;
        if(AllowUp){
            Direction=1;
        }else{
            Direction=-1;
        }

        if(VectorDistance(ball.GetCenter(),Vector2D{center.x,center.y+Direction*width/2.0})<= ball.GetRadius()){
            if(AllowUp){
                if(ball.getVelocity().y<0){
                    ball.setVelocity(Vector2D {ball.getVelocity().x,-ball.getVelocity().y});
                }
            }else{
                if(ball.getVelocity().y>0){
                    ball.setVelocity(Vector2D {ball.getVelocity().x,-ball.getVelocity().y});
                }
            }
        }
    }

    return Vector2D{0,0};
}
