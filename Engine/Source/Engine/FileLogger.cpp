#include <Engine/FileLogger.h>


Engine::FileLogger::FileLogger(const std::string& logFile)
{
    m_OutFile.exceptions(std::ios::badbit | std::ios::failbit);
    m_OutFile.open(logFile);
}

Engine::FileLogger::~FileLogger()
{
}

void Engine::FileLogger::PrintInfo(const std::string& message)
{
    m_OutFile << "INFO: " + message << '\n';
}

void Engine::FileLogger::PrintWarning(const std::string& message)
{
    m_OutFile << "WARNING: " + message << '\n';
}

void Engine::FileLogger::PrintError(const std::string& message)
{
    m_OutFile << "ERROR: " + message << '\n';
}