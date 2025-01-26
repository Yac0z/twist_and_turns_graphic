#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Player.h"
#include "Menu.h"
#include "GameState.h"

class Game {
public:
	Game();
	void run();

private:
	void handleEvents();
	void update();
	void render();

	sf::RenderWindow window;
	GameState currentState;
	sf::Font font;
	Menu menu;
	Grid grid;
	Player player1;
	Player player2;
	sf::RectangleShape inputBox;
	sf::Text inputText;
	sf::Text timerText;
	sf::RectangleShape enterButton;
	sf::Text enterText;
	std::string userInput;
	int scrollOffset;
	sf::Clock gameClock;
};

#endif // GAME_H
