#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>

int main() {
	// Window setup
	sf::RenderWindow window(sf::VideoMode(800, 600), "Grid Word Game");
	window.setFramerateLimit(60);

	// Load a font
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) { // Ensure you have a valid font file in the working directory
		std::cerr << "Failed to load font!" << std::endl;
		return -1;
	}

	// Create a grid object
	int gridX = 100; // Grid position X
	int gridY = 100; // Grid position Y
	int gridSize = 5; // 5x5 grid
	int cellSize = 50; // Each cell is 50x50 pixels
	// Create a Grid object
	Grid grid(100, 100, 10, 40, font);

	// Input variables
	std::string userInput; // Stores the user's current word

	// Text for displaying user input
	sf::Text inputText;
	inputText.setFont(font);
	inputText.setCharacterSize(24);
	inputText.setFillColor(sf::Color::Black);
	inputText.setPosition(100, 50); // Position above the grid

	// Game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Handle mouse clicks
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;
				grid.handleClick(mouseX, mouseY, userInput);
			}

			// Handle key presses for actions
			if (event.type == sf::Event::KeyPressed) {
				// Press Enter to validate the word
				if (event.key.code == sf::Keyboard::Enter) {
					if (grid.validateWord(userInput)) {
						std::cout << "Valid word: " << userInput << std::endl;
					}
					else {
						std::cout << "Invalid word: " << userInput << std::endl;
					}
					userInput.clear(); // Clear user input after validation
				}

				// Press H for a hint
				if (event.key.code == sf::Keyboard::H) {
					grid.provideHint(userInput);
				}
			}
		}

		// Update the user input text
		inputText.setString("Input: " + userInput);

		// Clear the window
		window.clear(sf::Color::White);

		// Draw the grid and input text
		grid.draw(window);
		window.draw(inputText);

		// Display the window
		window.display();
	}

	return 0;
}
