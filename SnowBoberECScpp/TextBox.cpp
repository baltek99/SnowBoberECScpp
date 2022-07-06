#include "TextBox.h"

TextBox::TextBox() {
	isSelected = false;
	hasLimit = false;
	limit = 0;
	textInBox.setString("_");
}

TextBox::TextBox(int size, sf::Color color, bool sel) {
	textInBox.setCharacterSize(size);
	textInBox.setFillColor(color);
	isSelected = sel;
	hasLimit = false;
	limit = 0;
	if (sel) {
		textInBox.setString("_");
	}
	else {
		textInBox.setString("");
	}
}

void TextBox::setFont(sf::Font& font) {
	textInBox.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos) {
	textInBox.setPosition(pos);
}

void TextBox::setLimit(bool boo) {
	hasLimit = boo;
}

void TextBox::setLimit(bool boo, int lim) {
	hasLimit = boo;
	limit = lim;
}

void TextBox::setSelected(bool sel) {
	isSelected = sel;
	if (!sel) {
		std::string t = text;
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		textInBox.setString(newT);
	}
}

std::string TextBox::getText() const {
	return text;
}

void TextBox::draw(sf::RenderWindow& window) {
	window.draw(textInBox);
}

void TextBox::typedOn(int charTyped) {
	if (isSelected) {
		if (charTyped < 128) {
			if (hasLimit && text.length() <= limit) {
				inputLogic(charTyped);
			}
			else if (!hasLimit) {
				inputLogic(charTyped);
			}
		}
	}
}

void TextBox::inputLogic(int charTyped) {
	if (charTyped == TAB_KEY)
		return;
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		
		text += static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.length() > 0) {
			deleteLastChar();
		}
	}
	textInBox.setString(text + "_");
}

void TextBox::deleteLastChar() {
	std::string t = text;
	std::string newT = "";

	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}
	text.clear();
	text = newT;

	textInBox.setString(text);
}
