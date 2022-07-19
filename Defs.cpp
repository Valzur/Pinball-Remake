#include "Defs.h"
using namespace Valzuroid::Pinball;

Vector2D Vector2D::zero = Vector2D{ 0, 0 };

double Valzuroid::Pinball::VectorDistance(Vector2D vector1, Vector2D vector2){
    double distance=pow((pow(vector1.x-vector2.x,2)+pow(vector1.y-vector2.y,2)),0.5);
    return distance;
}

double Valzuroid::Pinball::VectorNorm(Vector2D vector){
    double Norm=pow((pow(vector.x,2)+pow(vector.y,2)),0.5);
    return Norm;
}

Vector2D Valzuroid::Pinball::VectorDirection(Vector2D vector1,Vector2D vector2){
    Vector2D direction={vector2.x-vector1.x,vector2.y-vector2.y};
    direction=direction/Valzuroid::Pinball::VectorNorm(direction);
    return direction;
}

double Valzuroid::Pinball::lerp(double a,double b,double t){
    return a+t*(b-a);
};

bool Valzuroid::Pinball::FloatToBool(float number){
    if(number==1){
        return true;
    }else if (number==0){
        return false;
    }else {
        return NULL;
    }
}
double Valzuroid::Pinball::DotProduct(Vector2D u, Vector2D v){
   return u.x*v.x + u.y+v.y;
}