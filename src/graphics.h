#include "grid.h"
#include "grid_element.h"
#include <string>
#include <termios.h>
#include <unistd.h>
#pragma once 

namespace graphics {
void initialize_locales();
class Terminal {

  private:
    std::vector<std::wstring> current_frame;
    std::pair<int, int> dimensions;
    termios originalTerminal;
    termios currentTerminal;
    char current_keypress;

    void update_terminal_settings();
    void set_canonic(bool);
    void set_echo(bool);
    void set_vmin(unsigned char);
    void set_vtime(unsigned char);
    void enable_raw_mode() {
        set_canonic(false);
        set_echo(false);
        set_vmin(0);
        update_terminal_settings();
    }

  public:
    Terminal(const Terminal &obj) = delete;
    void draw(const std::vector<std::wstring> &frame);
    void fully_redraw(const std::vector<std::wstring> &frame);
    void erase_line();
    void erase_screen();
    void move_cursor_to_start();
    void hide_cursor();
    void show_cursor();
    void set_box_cursor();
    void move_to_start_of_next_line();
    void move_to_start_of_next_line(unsigned int jump_size);
    void move_cursor_to(int x, int y);
    void move_cursor_to(int x, int y, bool show);
    void move_cursor_to(const std::pair<int, int> &pos, bool show);
    std::string get_terminal_information();
    void reset_terminal();
    void update();
    void update_keypress();

    std::pair<int, int> get_cursor_position();
    std::pair<int, int> get_dimensions();
    bool pressed(char);
    void enter_alternate_buffer();
    void exit_alternate_buffer();

    Terminal() {
        tcgetattr(0, &originalTerminal);
        this->currentTerminal = originalTerminal;

        enter_alternate_buffer();
        move_cursor_to_start();
        enable_raw_mode();
    }
    ~Terminal() {
        reset_terminal();
        exit_alternate_buffer();
        show_cursor();
    }
};
} // namespace graphics
