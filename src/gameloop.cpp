#include "gameloop.h"
#include "../lib/inputUtils.h"
#include "graphics.h"
#include <atomic>
#include <functional>
#include <thread>
#include <unistd.h>

void gameloop::start_gameloop(std::atomic<bool> *quit, graphics::Terminal* terminal, std::function<void()> draw_function) {
    auto key_thread = keybind_thread(quit, terminal);
    char key = 0;
    while (!quit->load()) {
        draw_function();
    }
    key_thread.join();
}

std::thread gameloop::keybind_thread(std::atomic<bool> *quit, graphics::Terminal* terminal) {
    std::thread keybinds([=]() {
        while (!quit->load()) {
            auto c = terminal->read_current_char();
            if(c.has_value() && c == 'q'){
                quit->store(true);
            }
        }
    });
    return keybinds;
}
