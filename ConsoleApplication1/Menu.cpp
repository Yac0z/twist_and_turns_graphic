#include "Menu.h"

Menu::Menu(const sf::Font& font)
	: font(font), difficultyDropdownActive(false), themeDropdownActive(false), wordCount(3) {
	// Title Text
	titleText.setFont(font);
	titleText.setString("Game Menu");
	titleText.setCharacterSize(50);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(300, 50);

	// Start Button
	startButton.setSize(sf::Vector2f(200, 50));
	startButton.setFillColor(sf::Color::Green);
	startButton.setPosition(300, 500);

	startButtonText.setFont(font);
	startButtonText.setString("Start");
	startButtonText.setCharacterSize(30);
	startButtonText.setFillColor(sf::Color::White);
	startButtonText.setPosition(340, 510);

	// Difficulty Dropdown
	difficultyLabel.setFont(font);
	difficultyLabel.setString("Difficulty:");
	difficultyLabel.setCharacterSize(25);
	difficultyLabel.setFillColor(sf::Color::White);
	difficultyLabel.setPosition(100, 150);

	difficultyDropdown.setSize(sf::Vector2f(200, 50));
	difficultyDropdown.setFillColor(sf::Color::Blue);
	difficultyDropdown.setPosition(300, 150);

	difficultyOptions = { sf::Text("Easy", font, 20), sf::Text("Medium", font, 20), sf::Text("Hard", font, 20) };
	for (int i = 0; i < difficultyOptions.size(); ++i) {
		difficultyOptions[i].setPosition(310, 210 + i * 30);
		difficultyOptions[i].setFillColor(sf::Color::White);
	}
	selectedDifficulty = "Easy";

	// Theme Dropdown
	themeLabel.setFont(font);
	themeLabel.setString("Theme:");
	themeLabel.setCharacterSize(25);
	themeLabel.setFillColor(sf::Color::White);
	themeLabel.setPosition(100, 250);

	themeDropdown.setSize(sf::Vector2f(200, 50));
	themeDropdown.setFillColor(sf::Color::Blue);
	themeDropdown.setPosition(300, 250);

	themeOptions = { sf::Text("Singer", font, 20), sf::Text("Football", font, 20), sf::Text("Celebrities", font, 20) };
	for (int i = 0; i < themeOptions.size(); ++i) {
		themeOptions[i].setPosition(310, 310 + i * 30);
		themeOptions[i].setFillColor(sf::Color::White);
	}
	selectedTheme = "Singer";

	// Word Count Slider
	wordCountLabel.setFont(font);
	wordCountLabel.setString("Word Count: 3");
	wordCountLabel.setCharacterSize(25);
	wordCountLabel.setFillColor(sf::Color::White);
	wordCountLabel.setPosition(100, 350);

	sliderBar.setSize(sf::Vector2f(200, 5));
	sliderBar.setFillColor(sf::Color::White);
	sliderBar.setPosition(300, 380);

	sliderKnob.setSize(sf::Vector2f(10, 20));
	sliderKnob.setFillColor(sf::Color::Red);
	sliderKnob.setPosition(300, 370);
}

void Menu::displayMenu(sf::RenderWindow& window) {
	window.draw(titleText);

	// Draw start button
	window.draw(startButton);
	window.draw(startButtonText);

	// Draw difficulty dropdown
	window.draw(difficultyLabel);
	window.draw(difficultyDropdown);

	if (difficultyDropdownActive) {
		for (const auto& option : difficultyOptions) {
			window.draw(option);
		}
	}

	// Draw theme dropdown
	window.draw(themeLabel);
	window.draw(themeDropdown);

	if (themeDropdownActive) {
		for (const auto& option : themeOptions) {
			window.draw(option);
		}
	}

	// Draw word count slider
	window.draw(wordCountLabel);
	window.draw(sliderBar);
	window.draw(sliderKnob);
}

void Menu::handleEvents(sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		int mouseX = mousePos.x;
		int mouseY = mousePos.y;

		// Start Button
		if (startButton.getGlobalBounds().contains(mouseX, mouseY)) {
			// Start the game (this is where game start logic would go)
			std::cout << "Starting the game with:\n";
			std::cout << "Difficulty: " << selectedDifficulty << "\n";
			std::cout << "Theme: " << selectedTheme << "\n";
			std::cout << "Word Count: " << wordCount << "\n";
		}

		// Toggle difficulty dropdown
		if (difficultyDropdown.getGlobalBounds().contains(mouseX, mouseY)) {
			difficultyDropdownActive = !difficultyDropdownActive;
			themeDropdownActive = false; // Collapse the other dropdown
		}

		// Handle difficulty selection
		if (difficultyDropdownActive) {
			for (int i = 0; i < difficultyOptions.size(); ++i) {
				if (difficultyOptions[i].getGlobalBounds().contains(mouseX, mouseY)) {
					selectedDifficulty = difficultyOptions[i].getString();
					difficultyDropdownActive = false;
					break;
				}
			}
		}

		// Toggle theme dropdown
		if (themeDropdown.getGlobalBounds().contains(mouseX, mouseY)) {
			themeDropdownActive = !themeDropdownActive;
			difficultyDropdownActive = false; // Collapse the other dropdown
		}

		// Handle theme selection
		if (themeDropdownActive) {
			for (int i = 0; i < themeOptions.size(); ++i) {
				if (themeOptions[i].getGlobalBounds().contains(mouseX, mouseY)) {
					selectedTheme = themeOptions[i].getString();
					themeDropdownActive = false;
					break;
				}
			}
		}

		// Word count slider
		if (sliderKnob.getGlobalBounds().contains(mouseX, mouseY)) {
			sliderKnob.setPosition(std::clamp(mouseX, 300, 500), sliderKnob.getPosition().y);
			wordCount = 3 + (sliderKnob.getPosition().x - 300) / 25;
			wordCountLabel.setString("Word Count: " + std::to_string(wordCount));
		}
	}
}
