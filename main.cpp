
#include "lib/inputUtils.h"
#include "src/logging.h"
#include <fstream>
#include <unistd.h>

// TODO : 
// make a display biffer for the Grid so we don't remake a vector for everything.
// make cursor displayed on the Grid. 
// make a class for commands
//#define __DEBUG

std::atomic<bool> quit(false);

extern std::ofstream tty;

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 70);
    graphics::Terminal terminal;
#ifdef __DEBUG    
    gameloop::start_logging_thread(terminal);
#endif
    while (!quit.load()) {
        auto frame = grid.draw_grid();
        terminal.draw(frame);
        terminal.update_keypress();
        quit.store(terminal.pressed('q'));
    }


    return 0;
}
