#include "utils/logger.hpp"
#include <string>
#include <vector>
#include <filesystem>

namespace cs2opt {

// Warm the item schema cache so the first inventory open in a match
// doesn't stutter. Purely a disk-side optimisation; no memory writes.
class SkinPreloadService {
public:
    explicit SkinPreloadService(std::filesystem::path items_dir)
        : items_dir_(std::move(items_dir)) {}

    void preload() {
        if (!std::filesystem::exists(items_dir_)) {
            LOG_WARN("items dir {} missing, skipping preload",
                     items_dir_.string());
            return;
        }
        std::size_t n = 0;
        for (auto& entry : std::filesystem::recursive_directory_iterator(items_dir_)) {
            if (!entry.is_regular_file()) continue;
            const auto& p = entry.path();
            if (p.extension() == ".vtex" || p.extension() == ".vmat") {
                warm_file(p);
                ++n;
            }
        }
        LOG_INFO("skin preload finished: {} assets warmed", n);
    }

private:
    void warm_file(const std::filesystem::path& p) {
        // Touch the file to pull it into the OS cache.
        std::FILE* f = std::fopen(p.string().c_str(), "rb");
        if (!f) return;
        char buf[4096];
        std::fread(buf, 1, sizeof(buf), f);
        std::fclose(f);
    }

    std::filesystem::path items_dir_;
};

} // namespace cs2opt