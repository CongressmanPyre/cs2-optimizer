#pragma once
#include <filesystem>
#include <format>
#include <mutex>
#include <string>

namespace cs2opt {

enum class LogLevel { Debug, Info, Warn, Error };

class Logger {
public:
    static Logger& instance();

    void set_sink(const std::filesystem::path& file);
    void set_level(LogLevel lvl);

    template <typename... Args>
    void log(LogLevel lvl, std::format_string<Args...> fmt, Args&&... args) {
        if (lvl < level_) return;
        std::lock_guard lock(mu_);
        std::string line = std::format("[{}] ", tag(lvl));
        line += std::format(fmt, std::forward<Args>(args)...);
        line += '\n';
        write(line);
    }

private:
    void write(const std::string& line);
    static const char* tag(LogLevel lvl);

    std::mutex mu_;
    LogLevel   level_ = LogLevel::Info;
    std::FILE* sink_  = nullptr;
};

} // namespace cs2opt

#define LOG_DEBUG(...) ::cs2opt::Logger::instance().log(::cs2opt::LogLevel::Debug, __VA_ARGS__)
#define LOG_INFO(...)  ::cs2opt::Logger::instance().log(::cs2opt::LogLevel::Info,  __VA_ARGS__)
#define LOG_WARN(...)  ::cs2opt::Logger::instance().log(::cs2opt::LogLevel::Warn,  __VA_ARGS__)
#define LOG_ERROR(...) ::cs2opt::Logger::instance().log(::cs2opt::LogLevel::Error, __VA_ARGS__)