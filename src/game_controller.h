#include "command.h"
#include <algorithm>
class GameController {
  private:
    int x;
    int y;
    int xLimit;
    int yLimit;
    static GameController *instance;

    void displaceX(int jump) {
        x += jump;
        x = std::clamp(x, 0, xLimit);
    }
    void displaceY(int jump) {
        y += jump;
        y = std::clamp(y, 0, yLimit);
    }

    std::vector<command::command> commands = {
        command::command('h', [&]() { displaceX(-1); }),
        command::command('j', [&]() { displaceY(1); }),
        command::command('k', [&]() { displaceY(-1); }),
        command::command('l', [&]() { displaceX(1); }),
    };

    GameController() {}

  public:
    const int getX() { return x; }
    const int getY() { return y; }
    void setXLimit(const unsigned int max) { this->xLimit = max; }
    void setYLimit(const unsigned int max) { this->yLimit = max; }

    GameController(const GameController &) = delete;
    static GameController *getInstance() {
        if (!instance) {
            instance = new GameController();
        }
        return instance;
    }
    std::vector<command::command> &getCommands() { return commands; }
};
