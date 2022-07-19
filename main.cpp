#include "Game.h"
#include <iostream>
#include <direct.h>
#include <Windows.h>
#include <stdio.h>
#define cwd _getcwd
#define cd _chdir
using namespace Valzuroid::Pinball;

int main()
{
    //This is what they say, if it works don't touch it.
    //Nah, i'm joking (Kinda) these lines of code are responsible for hiding the console window as well as 
    //setting up the current working directory.
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    char buf[4096]; // never know how much is needed
    std::cout << "CWD: " << cwd(buf, sizeof buf) << std::endl;

    // Change working directory and test for success
    if (0 == cd("D:/Gamedev/C++ Projects/Pinball-Remake")) {
        std::cout << "CWD changed to: " << cwd(buf, sizeof buf) << std::endl;
    }
    // Create an object of the game.

    Valzuroid::Pinball::Game game;
    game.Initialize();
    while (!game.exited())
    {
        // Read new user (or whatever else)
        game.readInterfaceInput();
        // Simulate the game for one more frame
        game.simulate();
        // Update the game graphical interface
        game.updateInterfaceOutput();
    }
    return 0;
}