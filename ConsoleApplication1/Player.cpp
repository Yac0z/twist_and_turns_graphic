#include "Player.h"
#include "ButtonUtils.h"

Player::Player(const std::string& name, const sf::Font& font, const sf::Color& buttonColor, int x, int y)
	: name(name), score(0) {
	nameText.setString(name);
	nameText.setFont(font);
	nameText.setCharacterSize(20);
	nameText.setFillColor(sf::Color::White);
	nameText.setPosition(x, y);

	scoreText.setString("Score: 0");
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(x, y + 30);

	hintButton = createButton(x, y + 90, 100, 50, buttonColor);
	hintText.setString("Hint");
	hintText.setFont(font);
	hintText.setCharacterSize(20);
	hintText.setFillColor(sf::Color::White);
	hintText.setPosition(x + 10, y + 100);

	undoButton = createButton(x, y + 160, 100, 50, buttonColor);
	undoText.setString("Undo");
	undoText.setFont(font);
	undoText.setCharacterSize(20);
	undoText.setFillColor(sf::Color::White);
	undoText.setPosition(x + 10, y + 170);

	dictButton = createButton(x, y + 230, 100, 50, buttonColor);
	dictText.setString("Dict");
	dictText.setFont(font);
	dictText.setCharacterSize(20);
	dictText.setFillColor(sf::Color::White);
	dictText.setPosition(x + 10, y + 240);
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(nameText);
	window.draw(scoreText);
	window.draw(hintButton);
	window.draw(hintText);
	window.draw(undoButton);
	window.draw(undoText);
	window.draw(dictButton);
	window.draw(dictText);
}

void Player::updateScore(int score) {
	this->score = score;
	scoreText.setString("Score: " + std::to_string(score));
}
