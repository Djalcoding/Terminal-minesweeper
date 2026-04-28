#include "grid_element.h"
#include <string>
#include <vector>
#pragma once

class Grid {
  private:
    int width;
    int height;
    std::vector<std::vector<GridElement>> grid;
    std::vector<std::wstring> drawBuffer;
    void fillWithBombs(int bombCount);
    void incrementAroundBomb(int x, int y);
    void updateGrid();
    bool discoverDfs(int x, int y);

  public:
    Grid(int width, int height, int bombCount)
        : grid(std::vector<std::vector<GridElement>>(
              height, std::vector<GridElement>(width))),
          width(width), height(height) {
        fillWithBombs(bombCount);
        updateGrid();
    }

    std::vector<std::vector<GridElement>> *getGrid() { return &this->grid; }
    std::vector<std::wstring> &getWString() { return drawBuffer; }
    int get_height() { return this->height; }
    int get_width() { return this->width; }

    std::pair<int, int> getCursorPositionInGrid(int x, int y) {
        return {
            std::clamp(
                4 * (x) + 3, 
                0, 
                4 * width + 3),
            std::clamp(
                2 * (y + 1),
                0,
                2 * (height+1))};
    }
    bool discover(int x, int y) {
        bool result = discoverDfs(x, y);
        updateGrid();
        return result;
    }
};
