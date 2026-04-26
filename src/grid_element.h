#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#pragma once

class GridElement {
  public:
    enum class GridType { BOMB, NUMBER };
    enum class GridState { UNDISCOVERED, DISCOVERED, FLAGGED };

    GridElement();

    void setNumber(int value);
    void incrementNumber();
    void setType(GridType type);
    void setState(GridState state);
    bool isBomb();
    std::wstring getSymbol();
    bool discovered();
    std::optional<int> getNumber() { return number; }

  private:
    std::optional<int> number;
    GridType type;
    GridState state;
};
