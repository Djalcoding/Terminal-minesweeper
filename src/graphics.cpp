#include "graphics.h"
#include "../lib/vectorUtils.h"
#include "grid_element.h"
#include <iostream>
#include <locale>
#include <optional>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <utility>
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
    std::wcin.imbue(std::locale());
#endif
}

void graphics::Terminal::restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void graphics::Terminal::fully_redraw(std::vector<std::wstring> &frame) {
    erase_screen();
    move_cursor_to_start();
    for (std::wstring &line : frame) {
        std::wcout << line;
        move_to_start_of_next_line();
    }
    std::wcout << std::flush;
}

void graphics::Terminal::draw(std::vector<std::wstring> &frame) {
    std::pair<int, int> current_dimensions = get_dimensions();
    if (this->dimensions != current_dimensions) {
        this->dimensions = current_dimensions;
        fully_redraw(frame);
        return;
    }
    bool moved_to_start = false;
    int jump_size = 0;
    for (unsigned int i = 0; i < frame.size(); i++) {
        if (this->current_frame.size() > i &&
            this->current_frame[i] == frame[i]) {
            jump_size++;
        } else {
            if (!moved_to_start) {
                moved_to_start = true;
                move_cursor_to_start();
                hide_cursor();
            }
            if (jump_size > 0)
                move_to_start_of_next_line(jump_size);
            erase_line();
            std::wcout << frame[i];
            jump_size = 0;
        }
        move_to_start_of_next_line();
    }
    this->current_frame = frame;
    std::wcout << std::flush;
}

void graphics::Terminal::move_to_start_of_next_line() {
    std::wcout << "\033[1E" << std::flush;
}

void graphics::Terminal::move_to_start_of_next_line(unsigned int jump) {
    std::wstring jump_size = std::to_wstring(jump);
    std::wcout << (L"\033[" + jump_size + L"E") << std::flush;
}

void graphics::Terminal::erase_line() { std::wcout << "\033[2K" << std::flush; }
void graphics::Terminal::erase_screen() {
    std::wcout << "\033[2J" << std::flush;
}

void graphics::Terminal::move_cursor_to_start() { move_cursor_to(1, 1); }

void graphics::Terminal::hide_cursor() {
    std::wcout << "\033[?25l" << std::flush;
}

void graphics::Terminal::show_cursor() {
    std::wcout << "\033[?25h" << std::flush;
}

void graphics::Terminal::move_cursor_to(int x, int y) {
    move_cursor_to(x, y, false);
}

void graphics::Terminal::move_cursor_to(std::pair<int, int> pos, bool show) {
    move_cursor_to(pos.first, pos.second, show);
}

void graphics::Terminal::move_cursor_to(int x, int y, bool show) {
    std::wstring xComponent = std::to_wstring(x);
    std::wstring yComponent = std::to_wstring(y);
    std::wcout << (L"\033[" + yComponent + L";" + xComponent + L"H")
               << std::flush;
    if (show)
        show_cursor();
}

void graphics::Terminal::enter_alternate_buffer() {
    std::wcout << L"\033[?1049h" << std::flush;
}

void graphics::Terminal::exit_alternate_buffer() {
    std::wcout << L"\033[?1049l" << std::flush;
}

std::pair<int, int> graphics::Terminal::get_cursor_position() {
    char buf[30] = {0};
    int ret, i, pow;
    char ch;
    int x = 0;
    int y = 0;
    struct termios term, restore;

    tcgetattr(0, &term);
    tcgetattr(0, &restore);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);

    write(1, "\033[6n", 4);

    for (i = 0, ch = 0; ch != 'R'; i++) {
        ret = read(0, &ch, 1);
        if (!ret) {
            tcsetattr(0, TCSANOW, &restore);
            fprintf(stderr, "getpos: error reading response!\n");
            return {-1, -1};
        }
        buf[i] = ch;
        printf("buf[%d]: \t%c \t%d\n", i, ch, ch);
    }

    if (i < 2) {
        tcsetattr(0, TCSANOW, &restore);
        printf("i < 2\n");
        return {-1, -1};
    }

    for (i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
        x = x + (buf[i] - '0') * pow;

    for (i--, pow = 1; buf[i] != '['; i--, pow *= 10)
        y = y + (buf[i] - '0') * pow;

    tcsetattr(0, TCSANOW, &restore);
    return {x, y};
}

std::pair<int, int> graphics::Terminal::get_dimensions() {
    std::pair<int, int> startPos = get_cursor_position();
    move_cursor_to(99999, 99999);
    std::pair<int, int> dimensions = get_cursor_position();
    move_cursor_to(startPos, false);
    return dimensions;
}

std::optional<char> graphics::Terminal::read_current_char() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1) {
        return {};
    }
    return {c};
}
