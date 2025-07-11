#include "logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::logger_;

void Logger::initialize() {
    // Create console sink with color
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%n] %v");
    
    // Create logger
    logger_ = std::make_shared<spdlog::logger>("anashell", console_sink);
    logger_->set_level(spdlog::level::info);
    
    // Register as default logger
    spdlog::register_logger(logger_);
    spdlog::set_default_logger(logger_);
}

void Logger::set_level(spdlog::level::level_enum level) {
    if (logger_) {
        logger_->set_level(level);
    }
}