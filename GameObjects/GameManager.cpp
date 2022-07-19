#include "GameManager.h"
using namespace Valzuroid::Pinball::GameObjects;

GameManager::GameManager() {
    Score=0;
    lives=3;
}

void GameManager::addScore(int score) {
    if(timer<=0){
        AdditionalScore+=score;
        timer = ControlTimer;
    }
}

void GameManager::deductLives(int Lives) {
    lives-=Lives;
}

string GameManager::getLives() {
    return "Lives: " + to_string(lives);
}

void GameManager::Updategame(Interface & interface) {
    Score = Score + AdditionalScore;
    AdditionalScore = 0;
    //Generate Text values
    scoreText="Score: " + to_string(Score);
    livesText="Lives: " + to_string(lives);

    //Update Score
    interface.drawText(scoreText, 24, { GAME_WIDTH + (WINDOW_WIDTH - GAME_WIDTH) / 2.0, 20});
    //Update Lives
    interface.drawText(livesText, 24, { GAME_WIDTH + (WINDOW_WIDTH - GAME_WIDTH) / 2.0, 60});
}

void GameManager::ValueUpdate(Ball & ball, bool & IsLost) {
    //Detects lives deduction.
    if(ball.GetCenter().y>GAME_HEIGHT){
        ball.Reset();
        if (lives>0) {
            lives--;
        }else{
            IsLost=true;
        }
    }
}

void GameManager::EndGame(Interface & interface) {
    sf::RectangleShape Background(sf::Vector2f(GAME_WIDTH,GAME_HEIGHT)),
    Box(sf::Vector2f(600,300));

    //Aesthetics
    Background.setFillColor(sf::Color(240,240,240));
    Box.setFillColor(sf::Color(54, 79, 107));

    //Positioning
    Background.setOrigin(GAME_WIDTH/2.0,GAME_HEIGHT/2.0);
    Box.setOrigin(300,150);
    Background.setPosition(GAME_WIDTH/2.0,GAME_HEIGHT/2.0);
    Box.setPosition(WINDOW_WIDTH/2.0,GAME_HEIGHT/2.0);
    //Drawing
    interface.GetWindow().draw(Background);
    interface.GetWindow().draw(Box);
    // You lost text
    interface.drawText("YOU LOST", 48, {WINDOW_WIDTH/2.0-100, GAME_HEIGHT/2.0-100});
    //Final score text
    interface.drawText(scoreText, 48, {WINDOW_WIDTH/2.0-100, GAME_HEIGHT/2.0});
}

GameManager::GameManager(int Score, int lives) {
    this->Score=Score;
    this->lives=lives;
}

string GameManager::getScore() {
    return "Score: " + to_string(Score);
}

void GameManager::MultiplyScore(double Factor) {
    Score*=Factor;
}

void GameManager::UpdateTimer(double Time) {
    if(timer>0)
        timer-=Time;
}

void GameManager::Start()
{
    GameObject** allObjects = GetAllObjects();
    for (int i = 0; i < Count(); i++)
    {
        allObjects[i]->start();
    }
}

void GameManager::Update(double frameTime)
{
    GameObject** allObjects = GetAllObjects();
    for (int i = 0; i < Count(); i++)
    {
        allObjects[i]->updateTick(frameTime);
    }
}

void GameManager::MouseClickEvent(sf::Vector2i mousePosition)
{
    if (Mouse::isButtonPressed(sf::Mouse::Left) == wasClicked) return;

    GameObject** allObjects = GetAllObjects();

    if(Mouse::isButtonPressed(sf::Mouse::Left))
    {
        wasClicked = true;
        for (int i = 0; i < Count(); i++)
        {
            allObjects[i]->onMouseButtonDown(mousePosition);
        }
        return;
    }

    wasClicked = false;
    for (int i = 0; i < Count(); i++)
    {
        allObjects[i]->onMouseButtonUp(mousePosition);
    }
}
