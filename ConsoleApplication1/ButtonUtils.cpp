#include "ButtonUtils.h"


sf::RectangleShape createButton(int x, int y, int width, int height, sf::Color color) {
	sf::RectangleShape button(sf::Vector2f(width, height));
	button.setPosition(x, y);
	button.setFillColor(color);
	return button;
}