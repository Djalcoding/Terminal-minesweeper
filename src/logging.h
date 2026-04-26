#include <atomic>
#include <functional>
#include <optional>
#include <thread>
#include "graphics.h"
#pragma once


namespace gameloop {
    void start_logging_thread(graphics::Terminal&);

} // namespace gameloop
