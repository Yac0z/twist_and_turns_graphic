#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// Declare GameState enum in global scope
enum GameState {
	MenuState,
	GameState
};

const int gridSize = 10;  // Grid dimensions
const int cellSize = 40;  // Size of each grid cell

// Function to create a button
sf::RectangleShape createButton(int x, int y, int width, int height, sf::Color color) {
	sf::RectangleShape button(sf::Vector2f(width, height));
	button.setPosition(x, y);
	button.setFillColor(color);
	return button;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "2D Word Game");
	window.setFramerateLimit(60);

	// Fonts and text setup
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		return -1;
	}

	// Menu
	Menu menu;

	// Declare currentState variable
	std::string currentState = "MenuState";

	// Create the grid object
	Grid grid(200, 50, gridSize, cellSize, font);

	// Define layout dimensions
	int leftColumnWidth = 150;
	int rightColumnWidth = 150;
	int centerColumnWidth = 800 - leftColumnWidth - rightColumnWidth;

	// Player 1 - Buttons and Score
	sf::RectangleShape hintButton1 = createButton(20, 400, 100, 50, sf::Color(150, 75, 0));
	sf::Text hintText1("Hint", font, 20);
	hintText1.setFillColor(sf::Color::White);
	hintText1.setPosition(30, 410);

	sf::RectangleShape undoButton1 = createButton(20, 470, 100, 50, sf::Color(150, 75, 0));
	sf::Text undoText1("Undo", font, 20);
	undoText1.setFillColor(sf::Color::White);
	undoText1.setPosition(30, 480);

	sf::RectangleShape dictButton1 = createButton(20, 540, 100, 50, sf::Color(150, 75, 0));
	sf::Text dictText1("Dict", font, 20);
	dictText1.setFillColor(sf::Color::White);
	dictText1.setPosition(30, 550);

	sf::Text scoreText1("Score: 0", font, 20);
	scoreText1.setFillColor(sf::Color::White);
	scoreText1.setPosition(20, 340);

	sf::Text player1Name("Player 1", font, 20);
	player1Name.setFillColor(sf::Color::White);
	player1Name.setPosition(20, 310);

	// Player 2 - Buttons and Score
	sf::RectangleShape hintButton2 = createButton(650, 400, 100, 50, sf::Color(75, 150, 0));
	sf::Text hintText2("Hint", font, 20);
	hintText2.setFillColor(sf::Color::White);
	hintText2.setPosition(660, 410);

	sf::RectangleShape undoButton2 = createButton(650, 470, 100, 50, sf::Color(75, 150, 0));
	sf::Text undoText2("Undo", font, 20);
	undoText2.setFillColor(sf::Color::White);
	undoText2.setPosition(660, 480);

	sf::RectangleShape dictButton2 = createButton(650, 540, 100, 50, sf::Color(75, 150, 0));
	sf::Text dictText2("Dict", font, 20);
	dictText2.setFillColor(sf::Color::White);
	dictText2.setPosition(660, 550);

	sf::Text scoreText2("Score: 0", font, 20);
	scoreText2.setFillColor(sf::Color::White);
	scoreText2.setPosition(650, 340);

	sf::Text player2Name("Player 2", font, 20);
	player2Name.setFillColor(sf::Color::White);
	player2Name.setPosition(650, 310);

	// Center column: Matrix and Input box
	int gridX = leftColumnWidth + 50; // Start of the grid in the center
	int gridY = 50;                  // Top margin of the grid

	// Input Box
	sf::RectangleShape inputBox(sf::Vector2f(centerColumnWidth - 100, 50)); // Original size
	inputBox.setPosition(gridX, gridY + gridSize * cellSize + 20);
	inputBox.setFillColor(sf::Color::White);
	inputBox.setOutlineColor(sf::Color::Black);
	inputBox.setOutlineThickness(1);

	// Input Text inside the box
	sf::Text inputText("", font, 20);
	inputText.setFillColor(sf::Color::Black);
	inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 10);

	// Timer Text (placed below the input box, left side)
	sf::Text timerText("Time: 00.00s", font, 20);
	timerText.setFillColor(sf::Color::White);
	float timerX = inputBox.getPosition().x; // Align left with input box
	float timerY = inputBox.getPosition().y + inputBox.getSize().y + 20; // 20px below the input box
	timerText.setPosition(timerX, timerY);

	// Enter Button (placed next to the timer, right side)
	sf::RectangleShape enterButton(sf::Vector2f(100, 50)); // Adjust button size if needed
	float enterButtonX = timerText.getPosition().x + timerText.getLocalBounds().width + 190; // 20px gap to the right of the timer
	float enterButtonY = timerY; // Same vertical alignment as the timer
	enterButton.setPosition(enterButtonX, enterButtonY);
	enterButton.setFillColor(sf::Color::Green);

	// Enter Button Label
	sf::Text enterText("Enter", font, 20);
	enterText.setFillColor(sf::Color::White);
	float enterTextX = enterButton.getPosition().x + (enterButton.getSize().x - enterText.getLocalBounds().width) / 2;
	float enterTextY = enterButton.getPosition().y + (enterButton.getSize().y - enterText.getLocalBounds().height) / 2 - 5; // Center vertically
	enterText.setPosition(enterTextX, enterTextY);

	std::string userInput;
	int scrollOffset = 0;  // Horizontal scroll offset
	sf::Clock gameClock;

	// Main game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (currentState == "MenuState") {
				// Handle menu events
				if (menu.handleMenuEvents(window)) {
					currentState = "GameState"; // Transition to the game screen
				}
			}
			else if (currentState == "GameState") {
				// Handle game events
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						grid.handleClick(event.mouseButton.x, event.mouseButton.y, userInput);
						inputText.setString(userInput);
					}
				}

				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode == '\r') {
						std::cout << "Submitted: " << userInput << std::endl;
						userInput.clear();
						scrollOffset = 0;
					}
					else if (event.text.unicode < 128 && event.text.unicode != '\b') {
						continue;
					}
					else if (event.text.unicode == '\b' && !userInput.empty()) {
						userInput.pop_back();
					}
				}

				if (event.type == sf::Event::MouseButtonPressed) {
					if (enterButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						std::cout << "Submitted: " << userInput << std::endl;
						userInput.clear();
						scrollOffset = 0;
					}
				}
			}
		}

		if (currentState == "MenuState") {
			// Render the menu
			menu.renderMenu(window);
		}
		else if (currentState == "GameState") {
			// Update timer
			sf::Time elapsed = gameClock.getElapsedTime();
			std::stringstream timerStream;
			timerStream << "Time: " << std::fixed << std::setprecision(0) << elapsed.asSeconds() << "s";
			timerText.setString(timerStream.str());

			// Update scrolling
			float textWidth = inputText.getGlobalBounds().width;
			if (textWidth > inputBox.getSize().x - 20) {
				scrollOffset = textWidth - (inputBox.getSize().x - 20);
			}

			inputText.setString(userInput);
			inputText.setPosition(inputBox.getPosition().x + 10 - scrollOffset, inputBox.getPosition().y + 10);

			// Center timer text
			float timerX = gridX + (inputBox.getSize().x - timerText.getLocalBounds().width) / 2;
			timerText.setPosition(timerX, gridY + gridSize * cellSize + 80);

			// Rendering
			window.clear(sf::Color(200, 150, 100));

			// Draw Player 1
			window.draw(player1Name);
			window.draw(scoreText1);
			window.draw(hintButton1);
			window.draw(hintText1);
			window.draw(undoButton1);
			window.draw(undoText1);
			window.draw(dictButton1);
			window.draw(dictText1);

			// Draw Player 2
			window.draw(player2Name);
			window.draw(scoreText2);
			window.draw(hintButton2);
			window.draw(hintText2);
			window.draw(undoButton2);
			window.draw(undoText2);
			window.draw(dictButton2);
			window.draw(dictText2);

			// Draw center column (grid, input box, and timer)
			grid.draw(window);
			window.draw(inputBox);
			window.draw(inputText);
			window.draw(enterButton);
			window.draw(enterText);
			window.draw(timerText);

			window.display();
		}
	}

	return 0;
}