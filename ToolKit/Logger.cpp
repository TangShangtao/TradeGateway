#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>

void Logger::Init(level_enum level)
{
    spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::set_pattern("%L[%T.%f][%P][%t][%s:%#] %v");
    auto console = spdlog::stdout_color_mt("console");
    spdlog::stderr_color_mt("stderr");
    // spdlog::set_default_logger(console);

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* ptm = localtime(&now);
    char filename[60] = { 0 };
    sprintf(filename, "logs/run-%d-%02d-%02d.log", (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday);
    // Create a file rotating logger with 100mb size max and 30 rotated files
    auto max_size = 1024 * 1024 * 300;
    auto max_files = 10;
    spdlog::rotating_logger_mt("Service", filename, max_size, max_files);

//    spdlog::daily_logger_mt("Service", "logs/run.log", 0, 00);

    spdlog::set_default_logger(spdlog::get("Service"));
}