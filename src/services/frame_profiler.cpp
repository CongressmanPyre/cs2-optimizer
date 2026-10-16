#include "services/frame_profiler.hpp"
#include <algorithm>

namespace cs2opt {

void FrameProfiler::push(const FrameContext& frame) {
    window_[head_ % kWindow] = frame.frametime_ms;
    ++head_;
    ++total_;
}

void FrameProfiler::reset() {
    window_.fill(0.0f);
    head_ = 0;
    total_ = 0;
}

float FrameProfiler::avg_frametime_ms() const {
    if (total_ == 0) return 0.0f;
    float sum = 0.0f;
    for (float v : window_) sum += v;
    return sum / static_cast<float>(kWindow);
}

float FrameProfiler::p99_frametime_ms() const {
    auto sorted = window_;
    std::sort(sorted.begin(), sorted.end());
    return sorted[static_cast<std::size_t>(kWindow * 0.99)];
}

} // namespace cs2opt