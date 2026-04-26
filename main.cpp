
#include "lib/inputUtils.h"
#include "src/logging.h"
#include <fstream>
#include <unistd.h>
// #define __DEBUG

std::atomic<bool> quit(false);

extern std::ofstream tty;

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 10);
    graphics::Terminal terminal;
    gameloop::start_logging_thread(terminal);
    while (!quit.load()) {
        auto frame = grid.draw_grid();
        terminal.draw(frame);
        terminal.update_keypress();
        quit.store(terminal.pressed('q'));
    }


    return 0;
}
