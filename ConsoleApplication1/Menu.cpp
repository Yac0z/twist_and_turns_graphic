#include "Menu.h"
#include <iostream>

Menu::Menu() {
	if (!font.loadFromFile("Arial.ttf")) {
		throw std::runtime_error("Failed to load font");
	}

	titleText.setFont(font);
	titleText.setString("Game Menu");
	titleText.setCharacterSize(50);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(300, 50);

	startButton.setSize(sf::Vector2f(200, 50));
	startButton.setFillColor(sf::Color::Green);
	startButton.setPosition(300, 500);
	startButton.setOutlineThickness(2);
	startButton.setOutlineColor(sf::Color::Black);

	startButtonText.setFont(font);
	startButtonText.setString("Start");
	startButtonText.setCharacterSize(30);
	startButtonText.setFillColor(sf::Color::White);
	startButtonText.setPosition(340, 510);

	difficultyLabel.setFont(font);
	difficultyLabel.setString("Difficulty:");
	difficultyLabel.setCharacterSize(25);
	difficultyLabel.setFillColor(sf::Color::White);
	difficultyLabel.setPosition(100, 150);

	difficultyDropdown.setSize(sf::Vector2f(200, 50));
	difficultyDropdown.setFillColor(sf::Color::Blue);
	difficultyDropdown.setPosition(300, 150);
	difficultyDropdown.setOutlineThickness(2);
	difficultyDropdown.setOutlineColor(sf::Color::Black);

	difficultyOptions = { sf::Text("Easy", font, 20), sf::Text("Medium", font, 20), sf::Text("Hard", font, 20) };
	for (int i = 0; i < difficultyOptions.size(); ++i) {
		difficultyOptions[i].setPosition(310, 210 + i * 30);
		difficultyOptions[i].setFillColor(sf::Color::White);
	}
	difficultyDropdownActive = false;
	selectedDifficulty = "Easy";

	selectedDifficultyText.setFont(font);
	selectedDifficultyText.setCharacterSize(20);
	selectedDifficultyText.setFillColor(sf::Color::White);
	selectedDifficultyText.setPosition(310, 160);
	selectedDifficultyText.setString(selectedDifficulty);

	themeLabel.setFont(font);
	themeLabel.setString("Theme:");
	themeLabel.setCharacterSize(25);
	themeLabel.setFillColor(sf::Color::White);
	themeLabel.setPosition(100, 250);

	themeDropdown.setSize(sf::Vector2f(200, 50));
	themeDropdown.setFillColor(sf::Color::Blue);
	themeDropdown.setPosition(300, 250);
	themeDropdown.setOutlineThickness(2);
	themeDropdown.setOutlineColor(sf::Color::Black);

	themeOptions = { sf::Text("Singer", font, 20), sf::Text("Football", font, 20), sf::Text("Celebrities", font, 20) };
	for (int i = 0; i < themeOptions.size(); ++i) {
		themeOptions[i].setPosition(310, 310 + i * 30);
		themeOptions[i].setFillColor(sf::Color::White);
	}
	themeDropdownActive = false;
	selectedTheme = "Singer";

	selectedThemeText.setFont(font);
	selectedThemeText.setCharacterSize(20);
	selectedThemeText.setFillColor(sf::Color::White);
	selectedThemeText.setPosition(310, 260);
	selectedThemeText.setString(selectedTheme);

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

	wordCount = 3;
}

float Menu::getDropdownHeight(const std::vector<sf::Text>& options) {
	if (options.empty()) return 0.0f;
	return options.size() * (options[0].getGlobalBounds().height + 10);
}

void Menu::handleDropdownClick(sf::Vector2i mousePos, sf::RectangleShape& dropdown,
	std::vector<sf::Text>& options, std::string& selectedOption,
	bool& dropdownActive, bool& otherDropdownActive) {
	if (dropdown.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		dropdownActive = !dropdownActive;
		otherDropdownActive = false;
	}
	else if (dropdownActive) {
		for (int i = 0; i < options.size(); ++i) {
			if (options[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				selectedOption = options[i].getString();
				dropdownActive = false;
				break;
			}
		}
	}
}

void Menu::handleSliderClick(sf::Vector2i mousePos) {
	if (sliderBar.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		float newPosition = std::max(sliderBar.getPosition().x,
			std::min((float)mousePos.x, sliderBar.getPosition().x + sliderBar.getSize().x));
		sliderKnob.setPosition(newPosition, sliderKnob.getPosition().y);
		wordCount = 3 + (int)((newPosition - sliderBar.getPosition().x) / (sliderBar.getSize().x / 7));
		wordCountLabel.setString("Word Count: " + std::to_string(wordCount));
	}
}

bool Menu::handleMenuEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			return false;
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				return true; // Start button clicked
			}

			handleDropdownClick(mousePos, difficultyDropdown, difficultyOptions, selectedDifficulty, difficultyDropdownActive, themeDropdownActive);
			handleDropdownClick(mousePos, themeDropdown, themeOptions, selectedTheme, themeDropdownActive, difficultyDropdownActive);
			handleSliderClick(mousePos);
		}
	}
	return false;
}// Render the menu
void Menu::renderMenu(sf::RenderWindow& window) {
	// Calculate dropdown heights
	float difficultyHeight = difficultyDropdownActive ? getDropdownHeight(difficultyOptions) : 0.0f;
	float themeHeight = themeDropdownActive ? getDropdownHeight(themeOptions) : 0.0f;

	// Adjust positions dynamically for all elements
	difficultyLabel.setPosition(100, 150 ); // Difficulty label position (fixed)
	difficultyDropdown.setPosition(300, 150 ); // Difficulty dropdown position
	selectedDifficultyText.setPosition(310, 160 ); // Selected difficulty text position

	themeLabel.setPosition(100, 250 + difficultyHeight); // Theme label position
	themeDropdown.setPosition(300, 250 + difficultyHeight ); // Theme dropdown position
	selectedThemeText.setPosition(310, 260 + difficultyHeight ); // Selected theme text position

	wordCountLabel.setPosition(100, 350 + difficultyHeight + themeHeight); // Word count label position
	sliderBar.setPosition(300, 380 + difficultyHeight + themeHeight); // Slider bar position
	sliderKnob.setPosition(sliderKnob.getPosition().x, 370 + difficultyHeight + themeHeight); // Slider knob position

	startButton.setPosition(300, 500 + difficultyHeight + themeHeight); // Start button position
	startButtonText.setPosition(340, 510 + difficultyHeight + themeHeight); // Start button text position

	// Draw components
	window.clear(sf::Color(30, 30, 30)); // Dark background
	window.draw(titleText);

	// Draw difficulty dropdown
	window.draw(difficultyLabel);
	window.draw(difficultyDropdown);
	window.draw(selectedDifficultyText); // Draw selected difficulty text
	if (difficultyDropdownActive) {
		for (auto& option : difficultyOptions) {
			window.draw(option);
		}
	}

	// Draw theme dropdown
	window.draw(themeLabel);
	window.draw(themeDropdown);
	window.draw(selectedThemeText); // Draw selected theme text
	if (themeDropdownActive) {
		for (auto& option : themeOptions) {
			window.draw(option);
		}
	}

	// Draw slider
	window.draw(wordCountLabel);
	window.draw(sliderBar);
	window.draw(sliderKnob);

	// Draw start button
	window.draw(startButton);
	window.draw(startButtonText);

	window.display();
}

// Getters for selected values
std::string Menu::getSelectedDifficulty() const { return selectedDifficulty; }
std::string Menu::getSelectedTheme() const { return selectedTheme; }
int Menu::getWordCount() const { return wordCount; }