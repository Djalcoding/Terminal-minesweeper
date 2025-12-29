#include "grid_element.h"
#include <cstddef>
#include <optional>
#include <vector>
class Grid {
  private:
    int width;
    int height;
    std::vector<std::vector<GridElement>> grid;
    void fillWithBombs(int bombCount);
    void incrementAroundBomb(int x, int y);

  public:
    Grid(int width, int height, int bombCount)
        : grid(std::vector<std::vector<GridElement>>(
              height, std::vector<GridElement>(width))),
          width(width), height(height) {
        fillWithBombs(bombCount);
    }

    std::vector<std::vector<GridElement>>* getGrid();
};
