
#include "atomic"
#include "lib/inputUtils.h"
#include "src/game_controller.h"
#include "src/command.h"
#include "src/grid.h"
#include "src/logging.h"
#include <fstream>
#include <unistd.h>
// TODO :
// Accept arrow keys for input
// Add a background
#define __DEBUG
#define BoardX 9
#define BoardY 9

std::atomic<bool> quit(false);

extern std::ofstream tty;

int main() {
    graphics::initialize_locales();
    Grid grid(BoardX, BoardY, 10);
    graphics::Terminal terminal;
    GameController* game_controller = GameController::getInstance();
    game_controller->setXLimit(BoardX-1);
    game_controller->setYLimit(BoardY-1);
    std::vector<command::command> commands = game_controller->getCommands();
    commands.push_back({'q', [](){quit.store(true);}});
    commands.push_back({{'x','\n'}, [&](){grid.discover(game_controller->getX(), game_controller->getY());}});
    commands.push_back({'f', [&](){grid.flag(game_controller->getX(), game_controller->getY());}});
#ifdef __DEBUG
    using namespace std::chrono_literals;
    gameloop::start_logging_thread(terminal, 2000ms);
#endif
    while (!quit.load()) {
        auto frame = grid.getWString();
        terminal.update_keypress();
        terminal.draw(frame);
        terminal.show_cursor();
        terminal.set_box_cursor();
        for (auto command : commands) {
            command(terminal);
        }
        auto [xPos, yPos] = grid.getCursorPositionInGrid(game_controller->getX(), game_controller->getY());
        terminal.move_cursor_to(xPos, yPos);
    }

    return 0;
}
