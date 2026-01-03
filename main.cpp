#include "lib/inputUtils.h"
#include "src/graphics.h"
#include "src/grid.h"
#include <iostream>
#include <ostream>
#include <unistd.h>

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 10);
    bool running = true;
    int i = 0;
    int j = 0;
    std::wcout << L"\033[=3h" << std::flush;
    grid.discover(i, j);
    graphics::Screen screen;
    std::pair<int, int> dimension;
    while (running) {
        auto frame = grid.draw_grid();
        screen.draw(frame);
    }
    return 0;
}
