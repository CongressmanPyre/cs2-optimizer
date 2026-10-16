#include <cassert>
#include "services/optimizer_service.hpp"
#include "platform/process_adapter.hpp"

using namespace cs2opt;

// Smoke test using the real Windows adapter against a stub config.
int main() {
    OptimizerConfig cfg;
    cfg.forced_fps_cap = 240;
    cfg.per_map_fps.push_back({ "de_mirage", 300 });

    auto proc = make_process_adapter();
    OptimizerService svc(*proc, cfg);

    FrameContext fc;
    fc.current_map = "de_mirage";
    fc.in_match = true;
    fc.frametime_ms = 5.0f;
    svc.on_frame(fc);
    return 0;
}