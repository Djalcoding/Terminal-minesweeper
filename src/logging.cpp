#include "logging.h"
#include "../lib/inputUtils.h"
#include "graphics.h"
#include <chrono>
#include <fstream>
#include <ostream>
#include <thread>
#include <unistd.h>

extern std::ofstream tty;
void gameloop::start_logging_thread(graphics::Terminal &terminal, const std::chrono::duration<double>& throttle) {
    std::thread([&terminal, throttle]() {
            tty << "\n---------Thread start : " << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        while (true) {
            tty << "\e[0;37m"<< terminal.get_terminal_information() << std::flush;
            std::this_thread::sleep_for(throttle);
        }
    }).detach();
}
