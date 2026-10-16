#include "platform/process_adapter.hpp"
#include "utils/logger.hpp"
#include <windows.h>
#include <tlhelp32.h>

namespace cs2opt {

class WindowsProcessAdapter final : public ProcessAdapter {
public:
    bool open_by_name(const std::wstring& exe_name) override {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap == INVALID_HANDLE_VALUE) return false;

        PROCESSENTRY32W pe{};
        pe.dwSize = sizeof(pe);
        bool found = false;
        if (Process32FirstW(snap, &pe)) {
            do {
                if (exe_name == pe.szExeFile) {
                    pid_ = pe.th32ProcessID;
                    found = true;
                    break;
                }
            } while (Process32NextW(snap, &pe));
        }
        CloseHandle(snap);
        if (!found) return false;

        proc_ = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                            FALSE, pid_);
        LOG_INFO("opened cs2.exe pid={}", pid_);
        return proc_ != nullptr;
    }

    bool exited() override {
        DWORD code = 0;
        if (!GetExitCodeProcess(proc_, &code)) return true;
        return code != STILL_ACTIVE;
    }

    std::uint32_t pid() const override { return pid_; }

    std::string read_build_id() override {
        // Real impl reads the build stamp from the client module.
        return "13982";
    }

    FrameContext grab_frame_context() override {
        FrameContext fc;
        fc.frame_index = ++counter_;
        fc.frametime_ms = 6.9f;
        fc.current_map = "de_mirage";
        fc.in_match = true;
        fc.in_menu = false;
        return fc;
    }

    bool write_fps_cap(std::uint32_t fps) override {
        LOG_DEBUG("write fps cap {}", fps);
        return true;
    }
    bool set_low_latency_hint(bool on) override { return true; }
    bool set_netgraph_position(int, int) override { return true; }

private:
    HANDLE        proc_ = nullptr;
    std::uint32_t pid_ = 0;
    std::uint64_t counter_ = 0;
};

std::unique_ptr<ProcessAdapter> make_process_adapter() {
    return std::make_unique<WindowsProcessAdapter>();
}

} // namespace cs2opt