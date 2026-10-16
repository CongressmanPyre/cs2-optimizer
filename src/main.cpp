#include <cstdio>
#include <filesystem>
#include <string>

#include "bootstrap/entry_point.hpp"
#include "utils/logger.hpp"
#include "utils/config_loader.hpp"

int wmain(int argc, wchar_t** argv) {
    using namespace cs2opt;

    std::filesystem::path exe_dir =
        std::filesystem::path(argv[0]).parent_path();

    Logger::instance().set_sink(exe_dir / "logs" / "optimizer.log");
    Logger::instance().set_level(LogLevel::Info);

    ConfigLoader loader(exe_dir / "config");
    if (!loader.load_all()) {
        LOG_ERROR("config load failed: {}", loader.last_error());
        return 2;
    }

    EntryPoint entry(loader.config());
    if (!entry.attach_to_cs2()) {
        LOG_ERROR("could not attach to cs2.exe, is the game running?");
        return 3;
    }

    LOG_INFO("cs2-optimizer {} attached (build {})",
             CS2OPT_VERSION, entry.client_build_id());

    return entry.run_loop();
}