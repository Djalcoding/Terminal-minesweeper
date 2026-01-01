#include "graphics.h"
#include "../lib/vectorUtils.h"
#include "grid_element.h"
#include <iostream>
#include <locale>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <vector>

void graphics::initialize_locales() {
#if MS_STDLIB_BUGS
    constexpr char cp_utf16le[] = ".1200";
    setlocale(LC_ALL, cp_utf16le);
    _setmode(_fileno(stdout), _O_WTEXT);
#else
    constexpr char locale_name[] = "";
    setlocale(LC_ALL, locale_name);
    std::locale::global(std::locale(locale_name));
    std::wcout.imbue(std::locale());
#endif
}

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

std::vector<std::wstring> graphics::build_grid(Grid *grid) {
    std::vector<std::wstring> output_grid;
    std::vector<GridElement> flattened_elements =
        vectorUtils::flatten(*grid->getGrid());
    int width = grid->get_width();
    int heigth = grid->get_height();
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

void graphics::Screen::draw(std::vector<std::wstring> &frame) {
    move_cursor_to_start();
    hide_cursor();
    for (unsigned int i = 0; i < frame.size(); i++) {
        if (this->current_frame.size() > i &&
            this->current_frame[i] == frame[i]) {
        } else {
            erase_line();
            std::wcout << frame[i];
        }
        move_to_start_of_next_line();
    }
    this->current_frame = frame;
}

void graphics::Screen::move_to_start_of_next_line() {
    std::wcout << "\033[1E" << std::flush;
}

void graphics::Screen::erase_line() { std::wcout << "\033[2K" << std::flush; }

void graphics::Screen::move_cursor_to_start() { move_cursor_to(1, 1); }

void graphics::Screen::hide_cursor() {
    std::wcout << "\033[?25l" << std::flush;
}

void graphics::Screen::show_cursor() {
    std::wcout << "\033[?25h" << std::flush;
}

void graphics::Screen::move_cursor_to(int x, int y) {
    move_cursor_to(x, y, false);
}

void graphics::Screen::move_cursor_to(std::pair<int,int> pos, bool show) {
    move_cursor_to(pos.first, pos.second, show);
}

void graphics::Screen::move_cursor_to(int x, int y, bool show) {
    std::wstring xComponent = std::to_wstring(x);
    std::wstring yComponent = std::to_wstring(y);
    std::wcout << (L"\033[" + yComponent + L";" + xComponent + L"H")
               << std::flush;
    if (show) show_cursor();
}

void graphics::Screen::enter_alternate_buffer() {
    std::wcout << L"\033[?1049h" << std::flush;
}

void graphics::Screen::exit_alternate_buffer() {
    std::wcout << L"\033[?1049l" << std::flush;
}
