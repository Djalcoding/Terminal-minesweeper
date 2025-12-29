#include "grid_element.h"
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

const std::wstring color_white = L"\e[1;37m";
const std::wstring color_background_white = L"\e[0;107m";
const std::wstring color_green = L"\e[0;32m";
const std::wstring color_blue = L"\e[1;94m";
const std::wstring color_deep_blue = L"\e[0;34m";
const std::wstring color_cyan = L"\e[0;36m";
const std::wstring color_purple = L"\e[0;35m";
const std::wstring color_black = L"\e[0;30m";
const std::wstring color_red = L"\e[1;31m";
const std::wstring color_high_red = L"\e[1;91m";

std::unordered_map<int, std::wstring> numbers_to_color_map = {
    {0, color_black + L"■"},
    {1, color_blue + L"1"},
    {2, color_green + L"2"},
    {3, color_red + L"3"},
    {4, color_deep_blue + L"4"},
    {5, color_purple + L"5"},
    {6, color_cyan + L"6"},
    {7, color_black + L"7"},
    {8, color_background_white + L"8"},
};

GridElement::GridElement()
    : type(GridType::NUMBER), state(GridState::DISCOVERED), number({0}) {}

void GridElement::setNumber(int value) {
    if (type != GridType::NUMBER) {
        throw std::runtime_error("grid element is not a number");
    }
    GridElement::number = {value};
}
void GridElement::incrementNumber() {
    if (type != GridType::NUMBER) {
        return;
    }
    this->setNumber(this->number.value() + 1);
}

void GridElement::setState(GridState state) { this->state = state; }
void GridElement::setType(GridType type) {
    if (type == GridType::BOMB) {
        this->number = {};
    }
    this->type = type;
}

bool GridElement::isBomb() { return this->type == GridType::BOMB; }

std::wstring GridElement::getSymbol() {
    if (this->state == GridState::UNDISCOVERED) {
        return color_white + L'■';
    } else if (this->state == GridState::FLAGGED) {
        return color_red + L'▲';
    } else if (this->type == GridType::BOMB) {
        return color_high_red + L'¤';
    } else {
        return numbers_to_color_map[number.value()];
    }
}
