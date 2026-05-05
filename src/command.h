#include "graphics.h"
#include <functional>
#include <unordered_set>
#pragma once

namespace command {
struct command {
  private:
    std::unordered_set<char> keybinds;
    std::function<void()> callback;
    

  public:
    command(std::initializer_list<char> keybinds, std::function<void()> callback) : keybinds(keybinds), callback(callback){}
    command(char keybind, std::function<void()> callback) : keybinds({keybind}), callback(callback){}


    void operator() (const graphics::Terminal& terminal) {
        for (char bind : keybinds) {
            if (terminal.pressed(bind)) {
                callback();
                return;
            } 
        }
    }
};
} // namespace command
