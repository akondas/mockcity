#include "logger.hpp"

std::unique_ptr<Logger> g_logger = std::make_unique<Logger>();

void Logger::log(const LogLevel &level, const char *format, ...)
{
    #ifdef NDEBUG
    if (level == LogLevel::Debug) {
        return;
    }
    #endif

    std::stringstream ss;
    ss << "[";
    if (level == LogLevel::Debug) {
        ss << "Debug";
    } else if (level == LogLevel::Info) {
        ss << "Info";
    } else if (level == LogLevel::Warning) {
        ss << "Warning";
    } else if (level == LogLevel::Error) {
        ss << "Error";
    }

    ss << "] ";

    char buffer[512];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 512, format, args);
    va_end(args);

    ss << buffer << std::endl;

    std::cout << ss.str();
    std::cout.flush();

    if (file.is_open() && file.good()) {
        file << ss.str();
        file.flush();
    }
}
