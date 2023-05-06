#pragma once

#include <string>

// Interface for all the loggers

namespace Engine
{
    class Logger
    {
    public:
        virtual ~Logger() noexcept = default;

        virtual void PrintInfo(const std::string& message) = 0;
        virtual void PrintWarning(const std::string& message) = 0;
        virtual void PrintError(const std::string& error) = 0;
    };
}