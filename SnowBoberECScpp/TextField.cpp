#include "TextField.h"

TextField::TextField(sf::Font& font_) : Component(CmpId::TEXT_FIELD), textBox(25, sf::Color::Red, true), font(font_) {
    textBox.setFont(font);
}

TextField::TextField(std::string text_, sf::Font& font_) : Component(CmpId::TEXT_FIELD), text(text_), font(font_) {
}
