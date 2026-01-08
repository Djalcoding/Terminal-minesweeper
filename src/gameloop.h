#include <atomic>
#include <functional>
#include <optional>
#include <thread>
#include "graphics.h"
namespace gameloop {
    void start_gameloop(std::atomic<bool> *, graphics::Terminal* ,std::function<void()>);
    std::thread keybind_thread(std::atomic<bool> *,  graphics::Terminal* terminal);
} // namespace gameloop
