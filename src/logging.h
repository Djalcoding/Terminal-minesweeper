#include "graphics.h"
#include <chrono>
#pragma once


namespace gameloop {
    void start_logging_thread(graphics::Terminal&, const std::chrono::duration<double>& = std::chrono::seconds(0));

} // namespace gameloop
