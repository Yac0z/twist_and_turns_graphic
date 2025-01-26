#include "Game.h"
#include "ButtonUtils.h"
#include<iostream>

Game::Game()
	: window(sf::VideoMode(800, 600), "2D Word Game"),
	currentState(GameState::MenuState), // Use the enum class here
	player1("Player 1", font, sf::Color(150, 75, 0), 20, 310),
	player2("Player 2", font, sf::Color(75, 150, 0), 650, 310),
	scrollOffset(0) {
	window.setFramerateLimit(60);

	if (!font.loadFromFile("arial.ttf")) {
		throw std::runtime_error("Failed to load font");
	}

	inputBox.setSize(sf::Vector2f(500, 50));
	inputBox.setPosition(150, 450);
	inputBox.setFillColor(sf::Color::White);
	inputBox.setOutlineColor(sf::Color::Black);
	inputBox.setOutlineThickness(1);

	inputText.setFont(font);
	inputText.setCharacterSize(20);
	inputText.setFillColor(sf::Color::Black);
	inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 10);

	timerText.setFont(font);
	timerText.setCharacterSize(20);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(150, 510);

	enterButton = createButton(670, 450, 100, 50, sf::Color::Green);
	enterText.setFont(font);
	enterText.setString("Enter");
	enterText.setCharacterSize(20);
	enterText.setFillColor(sf::Color::White);
	enterText.setPosition(enterButton.getPosition().x + 20, enterButton.getPosition().y + 10);
}

void Game::run() {
	while (window.isOpen()) {
		handleEvents();
		update();
		render();
	}
}

void Game::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (currentState == GameState::MenuState) { // Use the enum class here
			if (menu.handleMenuEvents(window)) {
				currentState = GameState::GameState; // Use the enum class here
			}
		}
		else if (currentState == GameState::GameState) { // Use the enum class here
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
					userInput += static_cast<char>(event.text.unicode);
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
}

void Game::update() {
	if (currentState == GameState::GameState) { // Use the enum class here
		sf::Time elapsed = gameClock.getElapsedTime();
		std::stringstream timerStream;
		timerStream << "Time: " << std::fixed << std::setprecision(0) << elapsed.asSeconds() << "s";
		timerText.setString(timerStream.str());

		float textWidth = inputText.getGlobalBounds().width;
		if (textWidth > inputBox.getSize().x - 20) {
			scrollOffset = textWidth - (inputBox.getSize().x - 20);
		}

		inputText.setString(userInput);
		inputText.setPosition(inputBox.getPosition().x + 10 - scrollOffset, inputBox.getPosition().y + 10);
	}
}

void Game::render() {
	window.clear(sf::Color(200, 150, 100));

	if (currentState == GameState::MenuState) { // Use the enum class here
		menu.renderMenu(window);
	}
	else if (currentState == GameState::GameState) { // Use the enum class here
		player1.draw(window);
		player2.draw(window);
		grid.draw(window);
		window.draw(inputBox);
		window.draw(inputText);
		window.draw(enterButton);
		window.draw(enterText);
		window.draw(timerText);
	}

	window.display();
}