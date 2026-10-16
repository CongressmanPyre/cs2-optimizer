#pragma once
#include <array>
#include <cstdint>
#include "models/frame_context.hpp"

namespace cs2opt {

class FrameProfiler {
public:
    static constexpr std::size_t kWindow = 240;

    void push(const FrameContext& frame);
    void reset();

    float avg_frametime_ms() const;
    float p99_frametime_ms() const;
    std::uint64_t total_frames() const { return total_; }

private:
    std::array<float, kWindow> window_{};
    std::size_t head_ = 0;
    std::uint64_t total_ = 0;
};

} // namespace cs2opt