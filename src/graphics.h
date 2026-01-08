#include "grid.h"
#include "grid_element.h"
#include <string>
#include <termios.h>
#include <vector>
#include <unistd.h>
#pragma once

namespace graphics {
void initialize_locales();
class Terminal {

  private:
    std::vector<std::wstring> current_frame;
    std::pair<int,int> dimensions;

    
    struct termios oldt, newt;
  public:
    Terminal(const Terminal &obj) = delete;
    
    void restore_terminal();
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
    std::optional<char> read_current_char();
    Terminal() {
        enter_alternate_buffer();
        move_cursor_to_start();
    }
    ~Terminal() { restore_terminal(), exit_alternate_buffer(); show_cursor();}
};
} // namespace graphics
