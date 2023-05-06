#pragma once

#include "Game.h"

#include "Logger.h"

#define PRINT_INFO(message)                     \
{                                               \
    Game::Get().GetLogger().PrintInfo(message); \
}

#define PRINT_WARNING(message)                     \
{                                                  \
    Game::Get().GetLogger().PrintWarning(message); \
}

#define PRINT_ERROR(message)                     \
{                                                \
    Game::Get().GetLogger().PrintError(message); \
}
