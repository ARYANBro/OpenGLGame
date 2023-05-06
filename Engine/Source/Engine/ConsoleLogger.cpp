#include <Engine/ConsoleLogger.h>

#include <Windows.h>

#include <iostream>

Engine::ConsoleLogger::ConsoleLogger()
{
    m_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

Engine::ConsoleLogger::~ConsoleLogger() noexcept
{
}

void Engine::ConsoleLogger::PrintInfo(const std::string& message)
{
    Print("INFO: " + message, ConsoleColor::Green);
}

void Engine::ConsoleLogger::PrintWarning(const std::string& message)
{
    Print("WARNING: " + message, ConsoleColor::Yellow);
}

void Engine::ConsoleLogger::PrintError(const std::string& message)
{
    Print("ERROR: " + message, ConsoleColor::Red);
}

void Engine::ConsoleLogger::Print(const std::string& message, ConsoleColor color) const
{
    switch (color)
    {
    case ConsoleColor::Red:
        SetConsoleTextAttribute(m_Handle, FOREGROUND_RED);
        break;
    
    case ConsoleColor::Green:
        SetConsoleTextAttribute(m_Handle, FOREGROUND_GREEN);
        break;
    
    case ConsoleColor::Blue:
        SetConsoleTextAttribute(m_Handle, FOREGROUND_BLUE);
        break;

    case ConsoleColor::Yellow:
        SetConsoleTextAttribute(m_Handle, FOREGROUND_RED | FOREGROUND_GREEN);
        break;

    case ConsoleColor::None:
    default:
        break;
    }

    std::clog << message << std::endl;

    SetConsoleTextAttribute(m_Handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}