#pragma once

#include "Logger.h"

#include <fstream>

namespace Engine
{
    class FileLogger : public Logger
    {
    public:
        FileLogger(const std::string& logFilePath);
        virtual ~FileLogger() noexcept override;

        virtual void PrintInfo(const std::string& message) override;
        virtual void PrintWarning(const std::string& message) override;
        virtual void PrintError(const std::string& message) override;

    private:
        std::ofstream m_OutFile;
    };
}