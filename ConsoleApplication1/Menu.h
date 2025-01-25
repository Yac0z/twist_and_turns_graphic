#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
	Menu(); // Constructor

	// Handle menu events for a single frame
	bool handleMenuEvents(sf::RenderWindow& window);

	// Render the menu
	void renderMenu(sf::RenderWindow& window);

	// Getters for selected values
	std::string getSelectedDifficulty() const;
	std::string getSelectedTheme() const;
	int getWordCount() const;

private:
	// Font for text
	sf::Font font;

	// Title text
	sf::Text titleText;

	// Start button
	sf::RectangleShape startButton;
	sf::Text startButtonText;

	// Difficulty dropdown
	sf::Text difficultyLabel;
	sf::RectangleShape difficultyDropdown;
	std::vector<sf::Text> difficultyOptions;
	sf::Text selectedDifficultyText;
	bool difficultyDropdownActive;
	std::string selectedDifficulty;

	// Theme dropdown
	sf::Text themeLabel;
	sf::RectangleShape themeDropdown;
	std::vector<sf::Text> themeOptions;
	sf::Text selectedThemeText;
	bool themeDropdownActive;
	std::string selectedTheme;

	// Word count slider
	sf::Text wordCountLabel;
	sf::RectangleShape sliderBar;
	sf::RectangleShape sliderKnob;
	int wordCount;

	// Helper method for handling dropdown clicks
	void handleDropdownClick(sf::Vector2i mousePos, sf::RectangleShape& dropdown,
		std::vector<sf::Text>& options, std::string& selectedOption,
		bool& dropdownActive, bool& otherDropdownActive);

	// Helper method to calculate dropdown height
	float getDropdownHeight(const std::vector<sf::Text>& options);

	// Helper method for handling slider movement
	void handleSliderClick(sf::Vector2i mousePos);
};

#endif // MENU_H
