#include <cstddef>
#include <optional>
#include <string>
#include <iostream>
#pragma once

class GridElement {
  public:
    enum GridType { BOMB, NUMBER };
    enum GridState { UNDISCOVERED, DISCOVERED, FLAGGED };
    
    GridElement();

    void setNumber(int value);
    void incrementNumber();
    void setType(GridType type);
    void setState(GridState state);
    bool isBomb();
    std::wstring getSymbol();


    std::optional<int> getNumber() {
        return number;
    }
  private:
    std::optional<int> number;
    GridType type;
    GridState state;

};
