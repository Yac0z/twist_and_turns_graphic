#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
	Player(const std::string& name, const sf::Font& font, const sf::Color& buttonColor, int x, int y);

	void draw(sf::RenderWindow& window);
	void updateScore(int score);

private:
	std::string name;
	int score;
	sf::Text nameText;
	sf::Text scoreText;
	sf::RectangleShape hintButton;
	sf::Text hintText;
	sf::RectangleShape undoButton;
	sf::Text undoText;
	sf::RectangleShape dictButton;
	sf::Text dictText;
};

#endif // PLAYER_H