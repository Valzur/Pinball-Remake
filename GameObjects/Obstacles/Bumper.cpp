#include "Bumper.h"
using namespace Valzuroid::Pinball::GameObjects::Obstacles;

Bumper::Bumper(Vector2D pos, double rad, BumperType type): type(type) {
    position=pos;
    radius=rad;
    bscore=0;
}

void Bumper::setScorepoints(int x) {
    bscore = x;
}

