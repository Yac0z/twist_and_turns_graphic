#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Menu {
private:
	sf::Font font;  // Font for text elements
	sf::Text selectedDifficultyText; // Text to display selected difficulty
	sf::Text selectedThemeText;      // Text to display selected theme

	// Menu components
	sf::Text titleText;
	sf::RectangleShape startButton;
	sf::Text startButtonText;

	// Dropdown components
	sf::Text difficultyLabel;
	sf::RectangleShape difficultyDropdown;
	std::vector<sf::Text> difficultyOptions;
	bool difficultyDropdownActive;

	sf::Text themeLabel;
	sf::RectangleShape themeDropdown;
	std::vector<sf::Text> themeOptions;
	bool themeDropdownActive;

	// Word count slider components
	sf::Text wordCountLabel;
	sf::RectangleShape sliderBar;
	sf::RectangleShape sliderKnob;
	int wordCount;

	// Global selections
	std::string selectedDifficulty;
	std::string selectedTheme;

	// Helper methods
	void handleDropdownClick(sf::Vector2i mousePos, sf::RectangleShape& dropdown, std::vector<sf::Text>& options, std::string& selectedOption, bool& dropdownActive, bool& otherDropdownActive);
	void closeAllDropdowns();
	float getDropdownHeight(const std::vector<sf::Text>& options); // Helper to calculate dropdown height

public:
	Menu();
	void displayMenu(sf::RenderWindow& window);
	std::string getSelectedDifficulty() const;
	std::string getSelectedTheme() const;
	int getWordCount() const;
};

#endif // MENU_H