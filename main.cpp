#include "lib/inputUtils.h"
#include "src/graphics.h"
#include "src/grid.h"
#include <unistd.h>

int main() {
    graphics::initialize_locales();
    Grid grid(9, 9, 10);
    graphics::Screen screen;
    auto frame = graphics::build_grid(&grid);
    bool running = true;
    while (running) {
        screen.draw(frame);
    }
    return 0;
}
