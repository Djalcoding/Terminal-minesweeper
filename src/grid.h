#include "grid_element.h"
#include <stdexcept>
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
    void catchOoR(int x, int y);
    bool discoverDfs(int x, int y);
    GridElement& getNode(int x, int y) noexcept(false) {
        if (x < 0 || y <0 || y>= height || x >= width) {
            std::wcout << "AHH AT : " << x << y << '\n';
            throw std::out_of_range("Invalid index in grid"); 
        }
        return grid[y][x];
    }

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
    bool inBounds(const int x, const int y) {
        return !(x < 0 || y <0 || y>= height || x >= width);
    }

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

    /// Returns true if a bomb was discovered
    bool discover(int x, int y) {
        if (getNode(x, y).flagged()) {
            return false; 
        }
        bool result = discoverDfs(x, y);
        updateGrid();
        return result;
    }

    void flag(int x, int y);

};
