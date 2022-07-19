#include "CollisionDetection.h"
using namespace Valzuroid::Pinball::Utility;
using namespace Valzuroid::Pinball;

Vector2D Valzuroid::Pinball::Utility::CircleCollision(const Ball& ball, Vector2D position, double radius, double collision_time) {
    Vector2D Acceleration = {0, 0},Velocity;

        double ScalarVelocity = VectorNorm(ball.getVelocity());
        if (VectorDistance(ball.GetCenter(), position) < radius + ball.GetRadius()) {
            Velocity = ball.getVelocity() - (ball.GetCenter() - position) *
                    (DotProduct((ball.getVelocity()), (ball.GetCenter() - position))) /
                    pow(VectorNorm(position - ball.GetCenter()), 2);
            Velocity = Velocity / VectorNorm(Velocity);
            Acceleration = Vector2D {-Velocity.y,Velocity.x} * ScalarVelocity / collision_time;
        }
    return Acceleration;
}

bool Valzuroid::Pinball::Utility::BICCollision(Ball &ball, Vector2D position, double radius) {
    bool detected = false;
    if (VectorDistance(ball.GetCenter(), position) <= radius - ball.GetRadius())
        detected = true;

    return detected;
}

Vector2D Valzuroid::Pinball::Utility::Lcollision(const Ball& ball, Vector2D Position, double L, double W, double collision_time) {
    Vector2D Acceleration = { 0,0 }, v;
    bool isbetween = InRange(ball.GetCenter().x, Position.x + L/2, Position.x-L/2);
    if (isbetween && abs(ball.GetCenter().y - Position.y) <= ball.GetRadius()+W/2) {
        Acceleration = { ball.getVelocity().x * -2,ball.getVelocity().y * -2 };
        Acceleration = Acceleration / collision_time;
    }
    return Acceleration;

}
bool Valzuroid::Pinball::Utility::InRange(double value, double max, double min)
{
    return value >= min && value <= max;
}

Vector2D Valzuroid::Pinball::Utility::RectangleCollision(Ball &ball, double Length, double Width, double Angle, Vector2D Center) {
    Vector2D Velocity ={0,0}, DynamicCenter=Center, TDirection = {cos(Angle/180*PI),sin(Angle/180*PI)},
    NDirection = {TDirection.y,-TDirection.x};
    int Radius=ball.GetRadius(),NoOfIterations = Length/Radius;
    bool Signal = false;
    //Checking
    for (int i = 0; i < NoOfIterations; i++) {
        Vector2D NormalCenter1,NormalCenter2;
        double Distance1,Distance2;
        //Increment in the x axis
        DynamicCenter += TDirection * Radius;
        //Increment in the y axis
        NormalCenter1 = DynamicCenter + NDirection * Width/2.0;
        NormalCenter2 = DynamicCenter - NDirection * Width/2.0;
        //Check Distances
        Distance1 = VectorDistance(NormalCenter1,ball.GetCenter());
        Distance2 = VectorDistance(NormalCenter2,ball.GetCenter());

        if( Distance1 < ball.GetRadius() & Distance2 < ball.GetRadius() ){
            //It is close to both points
            if( Distance1 < Distance2 ){
                //Closer to point 1
                Velocity = ball.getVelocity() - NDirection*DotProduct(ball.getVelocity(),NDirection)/DotProduct(NDirection,NDirection) * 2;
                break;
            }else{
                //Closer to point 2
                Velocity = ball.getVelocity() + NDirection*DotProduct(ball.getVelocity(),NDirection*-1)/DotProduct(NDirection*-1,NDirection*-1) * 2;
                break;
            }
        } else if ( Distance1 < ball.GetRadius() ){
            //Closer to point 1
            Velocity = ball.getVelocity() - NDirection*DotProduct(ball.getVelocity(),NDirection)/DotProduct(NDirection,NDirection) * 2;
            break;
        } else if ( Distance2 < ball.GetRadius() ){
            //Closer to point 2
            Velocity = ball.getVelocity() + NDirection*DotProduct(ball.getVelocity(),NDirection*-1)/DotProduct(NDirection*-1,NDirection*-1) * 2;
            break;
        }
    }
    if(Velocity!=Vector2D{0,0}){
        Velocity = Velocity * VectorNorm(ball.getVelocity()) / VectorNorm(Velocity);
    }
    return Velocity;
}

CollisionResponse Valzuroid::Pinball::Utility::CircleLineCollision(Ball& ball, Vector2D center1, Vector2D center2)
{
    //Implementing: https://rosettacode.org/wiki/Line_circle_intersection#C.2B.2B.
    const double eps = 1 * (10) ^ 14;
    Vector2D ballCenter = ball.GetCenter();
    
    double A = center2.y - center1.y;
    double B = center1.x - center2.x;
    double C = center2.x * center1.y - center1.x * center2.y;
    double a = pow(A, 2.0) + pow(B, 2.0);
    double b, c;
    bool bnz = true;

    if (abs(B) >= eps) {
        b = 2 * (A * C + A * B * ballCenter.y - pow(B, 2.0) * ballCenter.x);
        c = pow(C, 2.0) + 2 * B * C * ballCenter.y - pow(B, 2.0) * (pow(ball.GetRadius(), 2.0) - pow(ballCenter.x, 2.0) - pow(ballCenter.y, 2.0));
    }
    else {
        b = 2 * (B * C + A * B * ballCenter.x - pow(A, 2.0) * ballCenter.y);
        c = pow(C, 2.0) + 2 * A * C * ballCenter.x - pow(A, 2.0) * (pow(ball.GetRadius(), 2.0) - pow(ballCenter.x, 2.0) - pow(ballCenter.y, 2.0));
        bnz = false;
    }
    auto d = pow(b, 2.0) - 4 * a * c; // discriminant

    if (d < 0)
    {
        return Vector2D::zero;
        //cout << "X: " << ballCenter.x << ", y: " << ballCenter.y << " , R: " << ball.GetRadius() << endl;
        //cout << "Center 1 x: " << center1.x << ", y: " << center1.y << endl;
        //cout << "Center 2 x: " << center2.x << ", y: " << center2.y << endl;
    }
    cout << "Intersection!" << endl;

    auto within = [center1, center2, eps](double x, double y) {
        auto d1 = sqrt(pow(center2.x - center1.x, 2.0) + pow(center2.y - center1.y, 2.0));  // distance between end-points
        auto d2 = sqrt(pow(x - center1.x, 2.0) + pow(y - center1.y, 2.0));    // distance from point to one end
        auto d3 = sqrt(pow(center2.x - x, 2.0) + pow(center2.y - y, 2.0));    // distance from point to other end
        auto delta = d1 - d2 - d3;
        return abs(delta) < eps;                    // true if delta is less than a small tolerance
    };

    auto fx = [A, B, C](double x) {
        return -(A * x + C) / B;
    };

    auto fy = [A, B, C](double y) {
        return -(B * y + C) / A;
    };

    auto rxy = [within](double x, double y) {
        if (within(x, y)) return Vector2D{ x, y };
    };

    double x, y;
    if (d == 0.0) 
    {
        // line is tangent to circle, so just one intersect at most
        if (bnz) {
            x = -b / (2 * a);
            y = fx(x);
            rxy(x, y);
        }
        else {
            y = -b / (2 * a);
            x = fy(y);
            rxy(x, y);
        }
    }
    else {
        // two intersects at most
        d = sqrt(d);
        if (bnz) {
            x = (-b + d) / (2 * a);
            y = fx(x);
            rxy(x, y);
            x = (-b - d) / (2 * a);
            y = fx(x);
            rxy(x, y);
        }
        else {
            y = (-b + d) / (2 * a);
            x = fy(y);
            rxy(x, y);
            y = (-b - d) / (2 * a);
            x = fy(y);
            rxy(x, y);
        }
    }

    return Vector2D::zero;
}

bool Valzuroid::Pinball::Utility::BOCCollision(Ball &ball, Vector2D position, double radius) {
    bool detected = false;
    if (VectorDistance(ball.GetCenter(), position) <= radius + ball.GetRadius() )
        detected = true;

    return detected;
}
