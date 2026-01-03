#include "grid.h"
#include "grid_element.h"
#include <string>
#include <vector>
#pragma once

namespace graphics {
void initialize_locales();
class Screen {

  private:
    std::vector<std::wstring> current_frame;
    std::pair<int,int> dimensions;

  public:
    Screen(const Screen &obj) = delete;

    void draw(std::vector<std::wstring> &frame);
    void fully_redraw(std::vector<std::wstring> &frame);
    void erase_line();
    void erase_screen();
    void move_cursor_to_start();
    void hide_cursor();
    void show_cursor();
    void move_to_start_of_next_line();
    void move_to_start_of_next_line(unsigned int jump_size);
    void move_cursor_to(int x, int y);
    void move_cursor_to(int x, int y, bool show);
    void move_cursor_to(std::pair<int,int> pos, bool show);
    std::pair<int,int> get_cursor_position();
    std::pair<int,int> get_dimensions();
    void enter_alternate_buffer();
    void exit_alternate_buffer();
    Screen() {
        enter_alternate_buffer();
        move_cursor_to_start();
    }
    ~Screen() { exit_alternate_buffer(); show_cursor();}
};
} // namespace graphics
