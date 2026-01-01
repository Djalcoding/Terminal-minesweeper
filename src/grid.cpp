#include "grid.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <vector>

void Grid::fillWithBombs(int bombCount) {
    if (bombCount > this->width * height) {
        throw std::runtime_error("more bombs than the grid size");
    }
    srand(time(0));
    std::vector<std::pair<int, int>> bombs;
    while (bombCount) {
        int x = rand() % this->width;
        int y = rand() % this->height;
        if (this->grid[y][x].isBomb()) {
            continue;
        }
        grid[y][x].setType(GridElement::GridType::BOMB);
        bombs.push_back({x, y});
        bombCount--;
    }

    for (auto bomb : bombs) {
        incrementAroundBomb(bomb.first, bomb.second);
    }
}

void Grid::incrementAroundBomb(int x, int y) {
    if (y > 0) {
        this->grid[y-1][x].incrementNumber();
    }

    if (y < this->height - 1) {
        grid[y + 1][x].incrementNumber();
    }

    if (x > 0) {
        this->grid[y][x-1].incrementNumber();
        if (y > 0) {
            this->grid[y - 1][x - 1].incrementNumber();
        }
        if (y < this->height - 1) {
            grid[y + 1][x - 1].incrementNumber();
        }
    }

    if (x < this->width - 1) {
        this->grid[y][x+1].incrementNumber();
        if (y > 0) {
            this->grid[y - 1][x + 1].incrementNumber();
        }
        if (y < this->height - 1) {
            grid[y + 1][x + 1].incrementNumber();
        }
    }
}

std::vector<std::vector<GridElement>> *Grid::getGrid() { return &this->grid; }


int Grid::get_height() {
    return this->height;
}

int Grid::get_width() {
    return this->width;
}
