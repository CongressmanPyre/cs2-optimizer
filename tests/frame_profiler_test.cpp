#include <cassert>
#include <cmath>
#include "services/frame_profiler.hpp"

using namespace cs2opt;

int main() {
    FrameProfiler p;
    for (int i = 0; i < 300; ++i) {
        FrameContext fc;
        fc.frametime_ms = 6.9f;
        fc.frame_index  = i;
        p.push(fc);
    }
    assert(p.total_frames() == 300);
    assert(std::fabs(p.avg_frametime_ms() - 6.9f) < 0.001f);
    return 0;
}