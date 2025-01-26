#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <utility>
#include <map> // Include for std::map

class Grid {
public:
	Grid(int x, int y, int size, int cellSize, const sf::Font& font); // Constructor

	void generateWordGrid();                     // Generate the word grid
	void draw(sf::RenderWindow& window);         // Draw the grid
	void handleClick(int mouseX, int mouseY, std::string& userInput); // Handle clicks for cell selection
	bool validateWord(const std::string& word);  // Validate the user's word
	void provideHint(std::string& userInput); // Provide hints for the current word

private:
	int gridX;                                   // X-coordinate of the grid's position
	int gridY;                                   // Y-coordinate of the grid's position
	int gridSize;                                // Size of the grid (e.g., 10x10)
	int cellSize;                                // Size of each cell in the grid
	const sf::Font& font;                        // Reference to the font used for text

	std::vector<std::vector<std::string>> words; // The grid of letters
	std::vector<std::vector<sf::RectangleShape>> cellShapes; // The grid of cells (rectangles)
	std::vector<std::pair<int, int>> selectedCells; // Coordinates of selected cells
	std::vector<std::string> validWords;         // List of valid words to find

	std::map<std::string, std::vector<std::pair<int, int>>> validWordCoordinates; // Map of valid words and their coordinates

	// Helper functions for word placement
	bool canPlaceWord(const std::string& word, int row, int col, int dRow, int dCol, const std::vector<std::vector<std::string>>& grid);
	void placeWord(const std::string& word, int row, int col, int dRow, int dCol, std::vector<std::vector<std::string>>& grid, std::vector<std::pair<int, int>>& wordCoords);
};

#endif // GRID_H
