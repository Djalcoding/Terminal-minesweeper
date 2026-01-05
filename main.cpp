#include "lib/inputUtils.h"
#include "src/graphics.h"
#include "src/grid.h"
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <thread>

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 10);
    bool running = true;
    int i = 0;
    int j = 0;
    grid.discover(i, j);
    graphics::Screen screen;
    auto frame = grid.draw_grid();
    screen.draw(frame);

    return 0;
}
