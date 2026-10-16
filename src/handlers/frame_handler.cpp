#include "handlers/frame_handler.hpp"
#include "services/optimizer_service.hpp"
#include "platform/overlay_adapter.hpp"

namespace cs2opt {

FrameHandler::FrameHandler(OptimizerService& svc, OverlayAdapter* overlay)
    : svc_(svc), overlay_(overlay) {}

void FrameHandler::on_frame(const FrameContext& frame) {
    svc_.on_frame(frame);
    if (overlay_ && frame.frame_index - last_overlay_frame_ >= 4) {
        render_overlay(frame);
        last_overlay_frame_ = frame.frame_index;
    }
}

void FrameHandler::render_overlay(const FrameContext& frame) {
    overlay_->begin_frame();
    overlay_->draw_text(16, 16, "cs2-optimizer");
    overlay_->draw_text(16, 32, "frametime: " +
        std::to_string(frame.frametime_ms) + " ms");
    overlay_->draw_text(16, 48, "map: " + frame.current_map);
    overlay_->end_frame();
}

} // namespace cs2opt