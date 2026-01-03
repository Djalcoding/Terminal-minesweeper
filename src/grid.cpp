#include "grid.h"
#include "../lib/vectorUtils.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <vector>

constexpr wchar_t left_side = L'┣';
constexpr wchar_t left_corner = L'┏';
constexpr wchar_t bottom_left_corner = L'┗';

constexpr wchar_t right_side = L'┫';
constexpr wchar_t right_corner = L'┓';
constexpr wchar_t bottom_right_corner = L'┛';

constexpr wchar_t horizontal_line = L'━';
constexpr wchar_t vertical_line = L'┃';
constexpr wchar_t caret = L'╋';
constexpr wchar_t top_caret = L'┳';
constexpr wchar_t bottom_caret = L'┻';

const std::wstring empty_space = L"\e[0;0m ";
std::vector<std::wstring> Grid::draw_grid() {
    std::vector<std::wstring> output_grid;
    std::vector<GridElement> flattened_elements =
        vectorUtils::flatten(this->getGrid());
    int width = this->get_width();
    int heigth = this->get_height();
    std::vector<GridElement>::iterator flattened_iterator =
        flattened_elements.begin();
    width *= 2;
    heigth *= 2;
    for (int y = 0; y <= heigth; y++) {
        std::wstring output_string;
        for (int x = 0; x <= width; x++) {
            if (y % 2 && x % 2) {
                output_string.append(empty_space);
                if (flattened_iterator != flattened_elements.end()) {
                    output_string.append(flattened_iterator->getSymbol());
                    flattened_iterator++;
                } else {
                    output_string.append(empty_space);
                }
                output_string.append(empty_space);
            } else if (x == 0) {
                if (y == 0)
                    output_string.push_back(left_corner);
                else if (y % 2) {
                    output_string.push_back(vertical_line);
                } else
                    output_string.push_back(y == heigth ? bottom_left_corner
                                                        : left_side);
            } else if (x == width) {
                if (y == 0)
                    output_string.push_back(right_corner);
                else if (y % 2) {
                    output_string.push_back(vertical_line);
                } else
                    output_string.push_back(y == heigth ? bottom_right_corner
                                                        : right_side);
            } else {
                if (x % 2) {
                    output_string.push_back(horizontal_line);
                    output_string.push_back(horizontal_line);
                    output_string.push_back(horizontal_line);
                } else if (y == 0) {
                    output_string.push_back(top_caret);
                } else if (y == heigth)
                    output_string.push_back(bottom_caret);
                else if (y % 2) {
                    output_string.push_back(vertical_line);
                } else
                    output_string.push_back(caret);
            }
        }
        output_grid.push_back(output_string);
    }

    return output_grid;
}

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
        this->grid[y - 1][x].incrementNumber();
    }

    if (y < this->height - 1) {
        grid[y + 1][x].incrementNumber();
    }

    if (x > 0) {
        this->grid[y][x - 1].incrementNumber();
        if (y > 0) {
            this->grid[y - 1][x - 1].incrementNumber();
        }
        if (y < this->height - 1) {
            grid[y + 1][x - 1].incrementNumber();
        }
    }

    if (x < this->width - 1) {
        this->grid[y][x + 1].incrementNumber();
        if (y > 0) {
            this->grid[y - 1][x + 1].incrementNumber();
        }
        if (y < this->height - 1) {
            grid[y + 1][x + 1].incrementNumber();
        }
    }
}

std::vector<std::vector<GridElement>> *Grid::getGrid() { return &this->grid; }

int Grid::get_height() { return this->height; }

int Grid::get_width() { return this->width; }

bool Grid::discover(int x, int y) {
    if(y >= grid.size() || y < 0 || x < 0 || x >= grid[0].size() || grid[y][x].discovered()) return false;
    this->grid[y][x].setState(GridElement::GridState::DISCOVERED);
    if (grid[y][x].getNumber().has_value() && grid[y][x].getNumber().value() == 0) {
        discover(x, y+1);
        discover(x, y-1);
        discover(x+1, y);
        discover(x+1, y+1);
        discover(x+1, y-1);
        discover(x-1, y);
        discover(x-1, y+1);
        discover(x-1, y-1);
    }
    return grid[y][x].isBomb();
}
