#pragma once
#include <cstdint>
#include <string>

namespace cs2opt {

struct FrameContext {
    std::uint64_t frame_index       = 0;
    std::uint64_t present_time_ns   = 0;
    float         frametime_ms      = 0.0f;
    float         gpu_busy_ms       = 0.0f;
    std::uint32_t current_map_hash  = 0;
    std::string   current_map;
    bool          in_match          = false;
    bool          in_menu           = true;
};

} // namespace cs2opt