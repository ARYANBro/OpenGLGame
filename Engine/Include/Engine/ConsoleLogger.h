#pragma once

#include <memory>

#include "Logger.h"

namespace Engine
{
    enum class ConsoleColor
    {
        None,
        Red,
        Green,
        Blue,
        Yellow
    };

    class ConsoleLogger : public Logger
    {
    public:
        ConsoleLogger();
        ConsoleLogger(const ConsoleLogger&) = delete;
        ConsoleLogger(ConsoleLogger&&) = delete;
        virtual ~ConsoleLogger() noexcept;

        virtual void PrintInfo(const std::string& message) override;
        virtual void PrintWarning(const std::string& message) override;
        virtual void PrintError(const std::string& message) override;

        virtual void Print(const std::string& message, ConsoleColor color = ConsoleColor::None) const;

    private:
        void* m_Handle;
    };
}
