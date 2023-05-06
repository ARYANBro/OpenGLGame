#include <Sandbox.h>

#include <iostream>

int main()
{
    try
    {
        std::unique_ptr<Engine::Game> Game = std::make_unique<Sandbox>();
        Game->Run();
    }
    catch (const std::exception& e)
    {
        return 1;
    }
}
