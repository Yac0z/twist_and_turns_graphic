#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Menu {
private:
	const sf::Font& font;

	// Title
	sf::Text titleText;

	// Start Button
	sf::RectangleShape startButton;
	sf::Text startButtonText;

	// Difficulty Dropdown
	sf::Text difficultyLabel;
	sf::RectangleShape difficultyDropdown;
	std::vector<sf::Text> difficultyOptions;
	bool difficultyDropdownActive;
	std::string selectedDifficulty;

	// Theme Dropdown
	sf::Text themeLabel;
	sf::RectangleShape themeDropdown;
	std::vector<sf::Text> themeOptions;
	bool themeDropdownActive;
	std::string selectedTheme;

	// Word Count Slider
	sf::Text wordCountLabel;
	sf::RectangleShape sliderBar;
	sf::RectangleShape sliderKnob;
	int wordCount;

public:
	Menu(const sf::Font& font);

	// Displays the menu screen
	void displayMenu(sf::RenderWindow& window);

	// Handles user input for the menu
	void handleEvents(sf::Event& event, sf::RenderWindow& window);

	// Getter methods to retrieve the user's choices
	std::string getSelectedDifficulty() const { return selectedDifficulty; }
	std::string getSelectedTheme() const { return selectedTheme; }
	int getWordCount() const { return wordCount; }
};

#endif // MENU_H
