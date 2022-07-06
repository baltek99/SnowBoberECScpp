#pragma once
#include "TextBox.h"
#include <string>

struct TextField {
public:
	std::string text;
	TextBox textBox;
	sf::Font& font;

	TextField(sf::Font& font_);

	TextField(std::string text_, sf::Font& font_);
};
