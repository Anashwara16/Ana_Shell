#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

class Logger {
public:
    static void initialize();
    static void set_level(spdlog::level::level_enum level);
    
    template<typename... Args>
    static void trace(const std::string& format, Args&&... args) {
        if (logger_) {
            logger_->trace(format, std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    static void debug(const std::string& format, Args&&... args) {
        if (logger_) {
            logger_->debug(format, std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    static void info(const std::string& format, Args&&... args) {
        if (logger_) {
            logger_->info(format, std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    static void warn(const std::string& format, Args&&... args) {
        if (logger_) {
            logger_->warn(format, std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    static void error(const std::string& format, Args&&... args) {
        if (logger_) {
            logger_->error(format, std::forward<Args>(args)...);
        }
    }
    
    template<typename... Args>
    static void critical(const std::string& format, Args&&... args) {
        if (logger_) {
            logger_->critical(format, std::forward<Args>(args)...);
        }
    }

private:
    static std::shared_ptr<spdlog::logger> logger_;
};