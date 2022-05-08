#include "InputManager.h"

InputManager::InputManager() : previousKey(sf::Keyboard::Key::Unknown), currentKey(sf::Keyboard::Key::Unknown) {
	released = true;
	justPressed = false;
	pressed = false;
}

void InputManager::update(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (!justPressed && !pressed) {
			justPressed = true;
			pressed = true;
			released = false;
		}
		else if (justPressed) {
			justPressed = false;
		}

		previousKey = currentKey;
		currentKey = event.key.code;
	}
	else if (event.type == sf::Event::KeyReleased) {
		previousKey = currentKey;
		currentKey = event.key.code;

		pressed = false;
		justPressed = false;
		released = true;
	} 
	
}

void InputManager::update() {
	if (justPressed) {
		justPressed = false;
	}
}

bool InputManager::isKeyJustPressed(sf::Keyboard::Key key) {
	return currentKey == key && justPressed;
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key) {
	return currentKey == key && pressed;
}

bool InputManager::isKeyReleased(sf::Keyboard::Key key) {
	return previousKey == key && released;
}