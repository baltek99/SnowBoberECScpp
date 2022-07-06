#pragma once
#include <SFML/Window.hpp>
#include <queue>

class InputManager
{
public:
	sf::Keyboard::Key previousKey;
	sf::Keyboard::Key currentKey;
	std::queue<int> charsTyped;
	bool released;
	bool justPressed;
	bool pressed;

	InputManager();

	void update(const sf::Event& event);

	void update();

	bool isKeyJustPressed(sf::Keyboard::Key key);

	bool isKeyPressed(sf::Keyboard::Key key);
	
	bool isKeyReleased(sf::Keyboard::Key key);

	void clear(std::queue<int>& q);
};
