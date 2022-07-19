#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Defs.h"
#include <iostream>

using namespace std;

// Represents the game interface
// This class is the ONLY one that interacts with the user
// This class is also the ONLY one aware of the graphics library being used
// That is, if the graphics library was to be changes, this class is the only thing to be changed
namespace Valzuroid {
    namespace Pinball {
        class Interface
        {
        private:
            string FPS;
            //Fonts and Texts
            sf::Font font;
            sf::Text text;
            sf::Text FPSText;
            sf::RenderWindow window;  // Represents the game window
            const sf::Color  // Colors used for drawing (can change the whole theme of the game)
                backgroundColor = sf::Color(240, 240, 240),
                textColor = sf::Color(252, 81, 133);
            const double outlineThickness = -2.0f;  // Negative sign means inwards

            //Sprites and textures

            sf::Texture LogoTexture;
            sf::Sprite LogoSprite;

        public:
            Interface();  // Constructor
            void drawLogo(float progress = 0);
            void getControls(bool& exit, bool& left, bool& right, bool& space);  // Detects the buttons pressed
            void setFPS(string fps);

            void clear();  // Clears the frame (first step in rendering a new frame)
            void display();  // Displays the frame (last step in rendering a new frame)

            //Utility
            void drawFPS();
            void drawText(string Text, int FontSize, Vector2D position);

            void LoadGraphics();
            void drawBackground();
            void drawUIBackground();


            sf::RenderWindow& GetWindow();
        };
    }
}