#pragma once
#include <SFML/Window.hpp>

class InputManager
{
public:
	sf::Keyboard::Key previousKey;
	sf::Keyboard::Key currentKey;
	bool released;
	bool justPressed;
	bool pressed;

	InputManager();

	void update(const sf::Event& event);

	void update();

	bool isKeyJustPressed(sf::Keyboard::Key key);

	bool isKeyPressed(sf::Keyboard::Key key);
	
	bool isKeyReleased(sf::Keyboard::Key key);
};

