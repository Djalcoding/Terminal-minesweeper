#include "grid_element.h"
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

static const std::wstring rgb_color(unsigned char r, unsigned char g, unsigned char b) {
    std::wstringstream ss;
    ss << L"\e[38;2;" << (int)r << L";" << (int)g << L";" << (int)b << L"m";
    return ss.str();
}
const std::wstring color_white = L"\e[1;37m";
const std::wstring color_gray = rgb_color(189, 189, 189);
const std::wstring color_dark_gray = rgb_color(128, 128, 128);
const std::wstring color_background_white = L"\e[0;107m";
const std::wstring color_green = rgb_color(62,189,21);
const std::wstring color_blue = rgb_color(0, 0, 255);
const std::wstring color_deep_blue = rgb_color(0, 0, 130);
const std::wstring color_cyan = rgb_color(0, 128, 129);
const std::wstring color_dark_red = rgb_color(135, 10, 0);
const std::wstring color_black = L"\e[0;30m";
const std::wstring color_red = rgb_color(253, 33, 18);
const std::wstring color_high_red = rgb_color(255, 0, 0);

const std::unordered_map<int, std::wstring> numbers_to_color_map = {
    {0, color_gray + L"■"},
    {1, color_blue + L"1"},
    {2, color_green + L"2"},
    {3, color_red + L"3"},
    {4, color_deep_blue + L"4"},
    {5, color_dark_red + L"5"},
    {6, color_cyan + L"6"},
    {7, color_black + L"7"},
    {8, color_dark_gray + L"8"},
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

bool GridElement::discovered() {
    return this->state == GridState::DISCOVERED;
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
        return numbers_to_color_map.at(number.value());
    }
}
