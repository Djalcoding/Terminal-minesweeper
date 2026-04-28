
#include "lib/inputUtils.h"
#include "src/logging.h"
#include <fstream>
#include <unistd.h>
#include "atomic"
#include "src/command.h"
#include "src/grid.h"
// TODO : 
// Accept arrow keys for input
// Add a background
#define __DEBUG


std::atomic<bool> quit(false);

extern std::ofstream tty;

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 10);
    graphics::Terminal terminal;
    int x = 0;
    int y = 0;
    

    const std::vector<command::command> commands = {
        command::command({'h','a'},[&]()mutable{x--;}),
        command::command({'l','d'},[&]()mutable{x++;}),
        command::command({'k','w'},[&]()mutable{y--;}),
        command::command({'s','j'},[&]()mutable{y++;})
    };

#ifdef __DEBUG    
    using namespace std::chrono_literals;
    gameloop::start_logging_thread(terminal,2000ms);
#endif
    while (!quit.load()) {
        auto frame = grid.getWString();
        terminal.update_keypress();
        terminal.draw(frame);
        quit.store(terminal.pressed('q'));
        terminal.show_cursor();
        terminal.set_box_cursor();
        for (auto command: commands) {
            command(terminal); 
        }
        auto [xPos,yPos] = grid.getCursorPositionInGrid(x, y);
        terminal.move_cursor_to(xPos,yPos);
    }


    return 0;
}
