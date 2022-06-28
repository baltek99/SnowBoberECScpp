#include "TextField.h"

TextField::TextField(sf::Font& font_) : textBox(25, sf::Color::Red, true), font(font_) {
    textBox.setFont(font);
}

TextField::TextField(std::string text_, sf::Font& font_) : text(text_), font(font_) {
}
