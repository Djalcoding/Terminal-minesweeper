#include "logging.h"
#include "../lib/inputUtils.h"
#include "graphics.h"
#include <fstream>
#include <thread>
#include <unistd.h>

extern std::ofstream tty;


void gameloop::start_logging_thread(graphics::Terminal &terminal) {
    std::thread([&]() {
        while (true) {
            tty << terminal.get_terminal_information();
        }
    }).detach();
}
