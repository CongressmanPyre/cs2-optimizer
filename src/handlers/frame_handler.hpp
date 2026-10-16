#pragma once
#include "models/frame_context.hpp"

namespace cs2opt {

class OptimizerService;
class OverlayAdapter;

class FrameHandler {
public:
    FrameHandler(OptimizerService& svc, OverlayAdapter* overlay);

    void on_frame(const FrameContext& frame);

private:
    void render_overlay(const FrameContext& frame);

    OptimizerService& svc_;
    OverlayAdapter*   overlay_;
    std::uint64_t     last_overlay_frame_ = 0;
};

} // namespace cs2opt