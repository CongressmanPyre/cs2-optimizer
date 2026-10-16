#include "bootstrap/entry_point.hpp"

#include "platform/process_adapter.hpp"
#include "platform/overlay_adapter.hpp"
#include "services/optimizer_service.hpp"
#include "handlers/frame_handler.hpp"
#include "utils/logger.hpp"

namespace cs2opt {

EntryPoint::EntryPoint(const OptimizerConfig& cfg) : cfg_(cfg) {}

EntryPoint::~EntryPoint() = default;

bool EntryPoint::attach_to_cs2() {
    process_ = make_process_adapter();
    if (!process_->open_by_name(L"cs2.exe")) {
        return false;
    }
    pid_      = process_->pid();
    build_id_ = process_->read_build_id();

    overlay_ = make_overlay_adapter();
    if (cfg_.enable_overlay && !overlay_->attach(pid_)) {
        LOG_WARN("overlay attach failed, continuing headless");
    }
    return true;
}

int EntryPoint::run_loop() {
    OptimizerService svc(*process_, cfg_);
    FrameHandler handler(svc, overlay_.get());

    while (!process_->exited()) {
        auto frame = process_->grab_frame_context();
        handler.on_frame(frame);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    return 0;
}

std::string EntryPoint::client_build_id() const { return build_id_; }
std::uint32_t EntryPoint::pid() const { return pid_; }

} // namespace cs2opt