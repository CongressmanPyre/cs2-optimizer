#pragma once
#include <string>
#include <filesystem>
#include "models/optimizer_config.hpp"

namespace cs2opt {

class ConfigHandler {
public:
    explicit ConfigHandler(std::filesystem::path config_dir);

    OptimizerConfig load();
    bool save(const OptimizerConfig& cfg);
    bool reload();

    const std::string& last_error() const { return last_error_; }

private:
    std::filesystem::path config_dir_;
    std::string           last_error_;
};

} // namespace cs2opt