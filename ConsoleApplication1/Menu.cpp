#include "Menu.h"

// Constructor
Menu::Menu() {
	// Load font
	if (!font.loadFromFile("Arial.ttf")) {
		throw std::runtime_error("Failed to load font");
	}

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
	startButton.setOutlineThickness(2);
	startButton.setOutlineColor(sf::Color::Black);

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
	difficultyDropdown.setOutlineThickness(2);
	difficultyDropdown.setOutlineColor(sf::Color::Black);

	difficultyOptions = { sf::Text("Easy", font, 20), sf::Text("Medium", font, 20), sf::Text("Hard", font, 20) };
	for (int i = 0; i < difficultyOptions.size(); ++i) {
		difficultyOptions[i].setPosition(310, 210 + i * 30); // Adjust vertical spacing
		difficultyOptions[i].setFillColor(sf::Color::White);
	}
	difficultyDropdownActive = false;
	selectedDifficulty = "Easy";

	// Selected Difficulty Text
	selectedDifficultyText.setFont(font);
	selectedDifficultyText.setCharacterSize(20);
	selectedDifficultyText.setFillColor(sf::Color::White);
	selectedDifficultyText.setPosition(310, 160);
	selectedDifficultyText.setString(selectedDifficulty);

	// Theme Dropdown
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
		themeOptions[i].setPosition(310, 310 + i * 30); // Adjust vertical spacing
		themeOptions[i].setFillColor(sf::Color::White);
	}
	themeDropdownActive = false;
	selectedTheme = "Singer";

	// Selected Theme Text
	selectedThemeText.setFont(font);
	selectedThemeText.setCharacterSize(20);
	selectedThemeText.setFillColor(sf::Color::White);
	selectedThemeText.setPosition(310, 260);
	selectedThemeText.setString(selectedTheme);

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

	wordCount = 3;
}

// Close all dropdowns
void Menu::closeAllDropdowns() {
	difficultyDropdownActive = false;
	themeDropdownActive = false;
}

// Helper method for dropdown click handling
void Menu::handleDropdownClick(sf::Vector2i mousePos, sf::RectangleShape& dropdown, std::vector<sf::Text>& options, std::string& selectedOption, bool& dropdownActive, bool& otherDropdownActive) {
	if (dropdownActive) {
		// Check if an option is clicked
		for (auto& option : options) {
			if (option.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				selectedOption = option.getString(); // Update selected option
				if (&dropdown == &difficultyDropdown) {
					selectedDifficultyText.setString(selectedOption); // Update difficulty text
				}
				else if (&dropdown == &themeDropdown) {
					selectedThemeText.setString(selectedOption); // Update theme text
				}
				dropdownActive = false; // Close dropdown
				break;
			}
		}
	}
	else if (dropdown.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		// Close the other dropdown
		otherDropdownActive = false;
		// Open the current dropdown
		dropdownActive = true;
	}
}
float Menu::getDropdownHeight(const std::vector<sf::Text>& options) {
	if (options.empty()) return 0.0f;
	return options.size() * (options[0].getGlobalBounds().height + 10); // 10 for spacing
}

// Display the menu
void Menu::displayMenu(sf::RenderWindow& window) {
	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				// Handle dropdowns
				handleDropdownClick(mousePos, difficultyDropdown, difficultyOptions, selectedDifficulty, difficultyDropdownActive, themeDropdownActive);
				handleDropdownClick(mousePos, themeDropdown, themeOptions, selectedTheme, themeDropdownActive, difficultyDropdownActive);

				// Handle slider
				if (sliderBar.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					sliderKnob.setPosition(mousePos.x, sliderKnob.getPosition().y);
					wordCount = 3 + (mousePos.x - sliderBar.getPosition().x) / 20; // Map position to range 3-10
					wordCount = std::min(std::max(wordCount, 3), 10); // Clamp between 3 and 10
					wordCountLabel.setString("Word Count: " + std::to_string(wordCount));
				}

				// Handle start button
				if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					return; // Exit the menu and start the game
				}
			}
		}

		// Calculate dropdown heights
		float difficultyHeight = difficultyDropdownActive ? getDropdownHeight(difficultyOptions) : 0.0f;
		float themeHeight = themeDropdownActive ? getDropdownHeight(themeOptions) : 0.0f;

		// Adjust positions dynamically
		themeDropdown.setPosition(300, 250 + difficultyHeight);
		sliderBar.setPosition(300, 380 + difficultyHeight + themeHeight);
		sliderKnob.setPosition(sliderKnob.getPosition().x, 370 + difficultyHeight + themeHeight);
		wordCountLabel.setPosition(100, 350 + difficultyHeight + themeHeight);
		startButton.setPosition(300, 500 + difficultyHeight + themeHeight);
		startButtonText.setPosition(340, 510 + difficultyHeight + themeHeight);

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
}
// Getters for selected values
std::string Menu::getSelectedDifficulty() const { return selectedDifficulty; }
std::string Menu::getSelectedTheme() const { return selectedTheme; }
int Menu::getWordCount() const { return wordCount; }