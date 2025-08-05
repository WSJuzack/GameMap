#include <iostream>
#include "Game.h"


int main()
{
    try
    {

        gl3::Game Hookmaster(1920, 1080, "Monkey's Escape");
        Hookmaster.run();

        return 0;
    }
    catch(const std::exception &e)
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }
}
