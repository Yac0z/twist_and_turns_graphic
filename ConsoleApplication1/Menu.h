#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
	Menu();

	// Handle menu events (clicks)
	bool handleMenuEvents(sf::RenderWindow& window);

	// Render the menu
	void renderMenu(sf::RenderWindow& window);

	// Getters for selected values
	std::string getSelectedDifficulty() const;
	std::string getSelectedTheme() const;
	int getWordCount() const;

private:
	// Private members for handling the menu UI components
	sf::Font font;

	sf::Text titleText;
	sf::RectangleShape startButton;
	sf::Text startButtonText;

	sf::Text difficultyLabel;
	sf::RectangleShape difficultyDropdown;
	std::vector<sf::Text> difficultyOptions;
	bool difficultyDropdownActive;
	std::string selectedDifficulty;
	sf::Text selectedDifficultyText;

	sf::Text themeLabel;
	sf::RectangleShape themeDropdown;
	std::vector<sf::Text> themeOptions;
	bool themeDropdownActive;
	std::string selectedTheme;
	sf::Text selectedThemeText;

	sf::Text wordCountLabel;
	sf::RectangleShape sliderBar;
	sf::RectangleShape sliderKnob;
	int wordCount;

	// Private methods to handle dropdown and slider interactions
	float getDropdownHeight(const std::vector<sf::Text>& options);
	void handleDropdownClick(sf::Vector2i mousePos, sf::RectangleShape& dropdown, std::vector<sf::Text>& options,
		std::string& selectedOption, bool& dropdownActive);
	void handleSliderClick(sf::Vector2i mousePos);
};

#endif // MENU_H
