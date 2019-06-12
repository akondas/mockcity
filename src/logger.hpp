#ifndef LOGGER_HPP
#define LOGGER_HPP


#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

enum class LogLevel : uint8_t
{
    Debug,
    Info,
    Warning,
    Error,
};

class Logger
{
    public:
        Logger() = default;
        ~Logger() = default;

        void setLogFilePath(const std::string &filePath) {
            file = std::ofstream{filePath, std::ios::out | std::ios::app};
        }

        void log(const LogLevel &level, const char *format, ...);

    private:
        std::ofstream file{};
};

extern std::unique_ptr<Logger> g_logger;

#endif
