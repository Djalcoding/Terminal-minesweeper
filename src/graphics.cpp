#include "graphics.h"
#include "../lib/vectorUtils.h"
#include "grid_element.h"
#include <iostream>
#include <locale>
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

const std::wstring empty_space = L"\e[0;37m ";

std::wstring
graphics::build_grid(uint width, uint heigth,
                     std::vector<std::vector<GridElement>> &grid_elements) {
    std::wstring output_string;
    std::vector<GridElement> flattened_elements =
        vectorUtils::flatten(grid_elements);
    std::vector<GridElement>::iterator flattened_iterator =
        flattened_elements.begin();
    width *= 2;
    heigth *= 2;
    for (int y = 0; y <= heigth; y++) {
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
        output_string.push_back(L'\n');
    }

    return output_string;
}
