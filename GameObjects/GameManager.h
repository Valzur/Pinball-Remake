#pragma once
#include <iostream>
#include "../Utility/Factory.h"
#include "../Interface.h"
#include "Ball.h"
using namespace std;
using namespace Valzuroid::Pinball::Utility;


namespace Valzuroid {
    namespace Pinball {
        namespace GameObjects {
            class Ball;

            class GameManager : public Factory<GameObject>
            {
            private:
                int Score;
                int lives;
                int AdditionalScore = 0;
                string scoreText;
                string livesText;
                double timer = ControlTimer;
                bool wasClicked = false;
            public:
                GameManager();
                GameManager(int Score, int lives);

                void addScore(int score);
                void deductLives(int Lives);

                //Getters
                string getLives();
                string getScore();

                //Update function
                void Updategame(Interface& interface);
                void ValueUpdate(Ball& ball, bool& Islost);
                void MultiplyScore(double Factor);
                void UpdateTimer(double Time);

                void Start();
                void Update(double frameTime);
                void MouseClickEvent(sf::Vector2i mousePosition);

                //Game lost
                void EndGame(Interface& interface);
            };
        }
    }
}