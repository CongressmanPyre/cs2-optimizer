#pragma once
#include <filesystem>
#include <string>
#include "models/optimizer_config.hpp"

namespace cs2opt {

class ConfigLoader {
public:
    explicit ConfigLoader(std::filesystem::path config_dir);

    bool load_all();
    const OptimizerConfig& config() const { return cfg_; }
    const std::string& last_error() const { return last_error_; }

private:
    bool load_main();
    bool load_map_profiles();
    bool load_offsets();

    std::filesystem::path config_dir_;
    OptimizerConfig       cfg_;
    std::string           last_error_;
};

} // namespace cs2opt