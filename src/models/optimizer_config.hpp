#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace cs2opt {

struct FpsCapRule {
    std::string map_name;
    int target_fps = 0;
};

struct OptimizerConfig {
    bool        enable_overlay        = true;
    bool        enable_fps_unlock     = true;
    bool        enable_netgraph_tweak = false;
    bool        enable_skin_preload   = true;
    bool        safe_mode             = false;
    int         forced_fps_cap        = 0;
    int         target_latency_ms     = 8;
    std::string preferred_gpu;
    std::vector<FpsCapRule> per_map_fps;
    std::string offsets_revision;
};

} // namespace cs2opt