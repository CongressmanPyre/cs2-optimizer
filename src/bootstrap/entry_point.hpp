#pragma once
#include <cstdint>
#include <string>
#include <memory>

#include "models/frame_context.hpp"
#include "models/optimizer_config.hpp"

namespace cs2opt {

class ProcessAdapter;
class OverlayAdapter;

class EntryPoint {
public:
    EntryPoint(const OptimizerConfig& cfg);
    ~EntryPoint();

    bool attach_to_cs2();
    int  run_loop();

    std::string client_build_id() const;
    std::uint32_t pid() const;

private:
    OptimizerConfig cfg_;
    std::unique_ptr<ProcessAdapter> process_;
    std::unique_ptr<OverlayAdapter> overlay_;
    std::uint32_t pid_ = 0;
    std::string build_id_;
};

} // namespace cs2opt