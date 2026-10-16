#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include "models/frame_context.hpp"

namespace cs2opt {

class ProcessAdapter {
public:
    virtual ~ProcessAdapter() = default;

    virtual bool open_by_name(const std::wstring& exe_name) = 0;
    virtual bool exited() = 0;
    virtual std::uint32_t pid() const = 0;
    virtual std::string read_build_id() = 0;

    virtual FrameContext grab_frame_context() = 0;
    virtual bool write_fps_cap(std::uint32_t fps) = 0;
    virtual bool set_low_latency_hint(bool on) = 0;
    virtual bool set_netgraph_position(int x, int y) = 0;
};

std::unique_ptr<ProcessAdapter> make_process_adapter();

} // namespace cs2opt