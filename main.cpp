#include "lib/inputUtils.h"
#include "src/gameloop.h"
#include "src/graphics.h"
#include "src/grid.h"
#include <unistd.h>

std::atomic<bool> quit(false);

void got_signal(int) { quit.store(true); }

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 10);
    graphics::Terminal terminal;
    
    auto keybind = gameloop::keybind_thread(&quit, &terminal);
    while (!quit.load()) {
        auto frame = grid.draw_grid();
        terminal.draw(frame); 
    }
    keybind.join();
    return 0;
}
