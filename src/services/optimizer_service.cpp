#include "services/optimizer_service.hpp"

#include "platform/process_adapter.hpp"
#include "services/frame_profiler.hpp"
#include "utils/logger.hpp"

namespace cs2opt {

OptimizerService::OptimizerService(ProcessAdapter& proc,
                                   const OptimizerConfig& cfg)
    : proc_(proc), cfg_(cfg), profiler_(new FrameProfiler()) {}

void OptimizerService::on_frame(const FrameContext& frame) {
    profiler_->push(frame);
    if (frame.current_map != active_map_ && !frame.current_map.empty()) {
        apply_map_profile(frame.current_map);
    }
    if (cfg_.target_latency_ms > 0) {
        tune_latency(frame);
    }
    if (cfg_.enable_netgraph_tweak) {
        tune_netgraph(frame);
    }
    if (cfg_.enable_fps_unlock && cfg_.forced_fps_cap > 0) {
        request_fps_cap(cfg_.forced_fps_cap);
    }
}

void OptimizerService::apply_map_profile(const std::string& map_name) {
    active_map_ = map_name;
    for (const auto& rule : cfg_.per_map_fps) {
        if (rule.map_name == map_name) {
            request_fps_cap(rule.target_fps);
            LOG_INFO("applied map profile for {}: fps={}", map_name,
                     rule.target_fps);
            return;
        }
    }
}

void OptimizerService::request_fps_cap(int fps) {
    if (fps == last_applied_cap_) return;
    if (proc_.write_fps_cap(static_cast<std::uint32_t>(fps))) {
        last_applied_cap_ = fps;
    }
}

void OptimizerService::tune_latency(const FrameContext& frame) {
    // Nudge the present-mode flags when frametime drifts above target.
    if (frame.frametime_ms > cfg_.target_latency_ms * 1.5f) {
        proc_.set_low_latency_hint(true);
    } else if (frame.frametime_ms < cfg_.target_latency_ms * 0.6f) {
        proc_.set_low_latency_hint(false);
    }
}

void OptimizerService::tune_netgraph(const FrameContext& frame) {
    if (!frame.in_match) return;
    proc_.set_netgraph_position(/*x=*/12, /*y=*/720);
}

void OptimizerService::flush() { profiler_->reset(); }

} // namespace cs2opt