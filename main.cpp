#include "src/graphics.h"
#include "src/grid.h"
#include <iostream>

int main() {
    graphics::initialize_locales();
    Grid grid(30,16,99);
    std::wcout << graphics::build_grid(30,16,*grid.getGrid());
    return 0;
}
