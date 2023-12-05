#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#define TRACE(...) SPDLOG_LOGGER_TRACE(spdlog::default_logger_raw(), __VA_ARGS__)
#define DEBUG(...) SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#define INFO(...) SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#define WARN(...) SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)
#define CRITICAL(...) SPDLOG_LOGGER_CRITICAL(spdlog::default_logger_raw(), __VA_ARGS__)

// #define TRACE(...) spdlog::trace(__VA_ARGS__)
// #define DEBUG(...) spdlog::debug(__VA_ARGS__)
// #define INFO(...) spdlog::info(__VA_ARGS__)
// #define WARN(...) spdlog::warn(__VA_ARGS__)
// #define ERROR(...) spdlog::error(__VA_ARGS__)
// #define CRITICAL(...) spdlog::critical(__VA_ARGS__)

#define LEVEL_TRACE 0
#define LEVEL_DEBUG 1
#define LEVEL_INFO 2
#define LEVEL_WARN 3
#define LEVEL_ERROR 4
#define LEVEL_CRITICAL 5
#define LEVEL_OFF 6

class Logger
{
public:
    enum level_enum
    {
        trace = LEVEL_TRACE,
        debug = LEVEL_DEBUG,
        info = LEVEL_INFO,
        warn = LEVEL_WARN,
        err = LEVEL_ERROR,
        critical = LEVEL_CRITICAL,
        off = LEVEL_OFF,
        n_levels
    };

    static void Init(level_enum level);
};