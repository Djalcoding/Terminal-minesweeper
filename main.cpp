
#include "lib/inputUtils.h"
#include "src/logging.h"
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include "atomic"
// TODO : 
// make a display biffer for the Grid so we don't remake a vector for everything.
// make cursor displayed on the Grid. 
// make a class for commands
#define __DEBUG


std::atomic<bool> quit(false);

extern std::ofstream tty;

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 10);
    graphics::Terminal terminal;
    int x = 0;
    int y = 0;
#ifdef __DEBUG    
    using namespace std::chrono_literals;
    //gameloop::start_logging_thread(terminal,2000ms);
#endif
    while (!quit.load()) {
        auto frame = grid.getWString();
        terminal.update_keypress();
        terminal.draw(frame);
        if(terminal.pressed('h')) {
            x--;
            x = std::clamp(x,0, 8);
        }
        if(terminal.pressed('l')) {
            x++;
            x = std::clamp(x,0, 8);
        }
        if(terminal.pressed('j')) {
            y++;
            y = std::clamp(y,0, 8);
        }
        if(terminal.pressed('k')) {
            y--;
            y = std::clamp(y,0, 8);
        }
        if(terminal.pressed('x')) {
            grid.discover(x, y);
        }
        quit.store(terminal.pressed('q'));
        terminal.show_cursor();
        terminal.set_box_cursor();
        auto [xPos,yPos] = grid.getCursorPositionInGrid(x, y);
        terminal.move_cursor_to(xPos,yPos);
    }


    return 0;
}
