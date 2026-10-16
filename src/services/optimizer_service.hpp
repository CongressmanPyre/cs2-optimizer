#pragma once
#include "models/optimizer_config.hpp"
#include "models/frame_context.hpp"

namespace cs2opt {

class ProcessAdapter;
class FrameProfiler;

class OptimizerService {
public:
    OptimizerService(ProcessAdapter& proc, const OptimizerConfig& cfg);

    void on_frame(const FrameContext& frame);
    void apply_map_profile(const std::string& map_name);
    void request_fps_cap(int fps);
    void flush();

private:
    void tune_latency(const FrameContext& frame);
    void tune_netgraph(const FrameContext& frame);

    ProcessAdapter&     proc_;
    OptimizerConfig     cfg_;
    FrameProfiler*      profiler_;
    std::string         active_map_;
    int                 last_applied_cap_ = -1;
};

} // namespace cs2opt