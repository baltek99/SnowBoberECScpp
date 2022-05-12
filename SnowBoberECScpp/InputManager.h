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

class InputManager2 {
public:
	std::vector<bool> previous;
	std::vector<bool> current;

	void update() {
		previous = current;
		current.clear();
	}

	void setKeyUp(sf::Keyboard::Key key) {
		// TODO: alokowanie i rozszerzanie vektora ze stanem przyciskow. Dobrze by by³o trzymaæ je jako kod ASCII bo s¹ ma³e.
		current[key] = true;
	}
	void setKeyDown(sf::Keyboard::Key key) {
		current[key] = false;
	}

	bool isKeyPressed(sf::Keyboard::Key k) {
		return !previous[k] && current[k];
	}
	bool isKeyReleased(sf::Keyboard::Key k) {
		return previous[k] && !current[k];
	}
	bool isKeyDown(sf::Keyboard::Key k) {
		return previous[k] && current[k];
	}
	bool isKeyUp(sf::Keyboard::Key k) {
		return !previous[k] && !current[k];
	}


};