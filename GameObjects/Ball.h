#pragma once
#include "Obstacles/Obstacle.h"
#include "GameManager.h"
#include <iostream>
#include "../Defs.h"
#include "../../Utility/AudioManager.h"

namespace Valzuroid {
    using namespace Pinball;
    namespace Pinball {
        namespace GameObjects {
            // Represents the ball (the single most important object in a Pinball game!)
            class Ball : public Drawn, public AudioManager
            {
            private:
                const Vector2D initialPosition, initialVelocity;
                bool isActive, isMain, isUsedPortal = false, isUsedLane = false;
                const double radius, boostDuration = 0.5, scalarVelocity = 300.0;
                Vector2D center;  //The instantaneous center of the ball
                Vector2D velocity;  //The instantaneous velocity of the ball
                Vector2D acceleration;
                double boostTimer = 0.0, speedBoost = 1.0;

                //Lane Attributes
                double laneLength = 0;
                bool isDirectedUp = false;

                const double outlineThickness = -2.0f;
                const sf::Color outlineColor = sf::Color(54, 79, 107);
                const sf::Color ballFillColor = sf::Color::White;

                sf::Texture Balltexture;
                sf::Sprite Ballsprite;

            public:
                explicit Ball(
                    Vector2D center = INITIAL_CENTER,
                    float radius = 10,
                    Vector2D velocity = INITIAL_VELOCITY,
                    bool Main = true);  // Constructor

                // Accessors
                float GetRadius() const;
                Vector2D GetCenter() const;
                Vector2D getVelocity() const;
                Vector2D getAcceleration() const;
                bool getisMain() const;
                bool getIsUsedPortal() const;
                bool GetLaneMode() const;

                void setUsedPortal(bool Used);
                void setCenter(Vector2D pos);
                void setVelocity(Vector2D vel);
                void setAcceleration(Vector2D Acceleration);
                void SetLaneLength(double Length);
                void SetLaneDirection(bool isUp);
                void SetLaneMode(bool Active);

                void deActivate();
                void Activate(bool& space);
                void Reset();
                void Boost(double BoostValue);
                void UpdateBoost(double time);

                Vector2D collideWith(Ball& ball, float collision_time, GameManager& manager);

                void move(double time, GameManager& manager, bool& lost);  // Simulates the ball's motion under uniform acceleration for a period of time

                void start() override;
                void draw(Interface& interface) override;
            };
        }
    }
}