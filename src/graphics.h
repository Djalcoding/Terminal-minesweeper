#include <string>
#include <vector>
#include "grid_element.h"
namespace graphics {
    void initialize_locales();
    std::wstring build_grid(uint width, uint heigth, std::vector<std::vector<GridElement>>& grid_elements);
}
