#include "grid_element.h"
#include <cstddef>
#include <optional>
#include <vector>
#pragma once

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

    std::vector<std::vector<GridElement>> *getGrid();
    std::vector<std::wstring> draw_grid();
    int get_height();
    int get_width();
    std::pair<int, int> getCursorPositionInGrid(int x, int y) {
        return {4*(x)+3,2*(y+1)};
    }

    bool discover(int x, int y);
};
