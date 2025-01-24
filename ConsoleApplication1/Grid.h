#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Grid {
private:
	int gridX, gridY;                        // Top-left corner of the grid
	int gridSize;                            // Number of cells per row/column
	int cellSize;                            // Size of each cell
	const sf::Font& font;                    // Reference to the font
	std::vector<std::vector<std::string>> words; // Words in the grid
	std::vector<std::vector<sf::RectangleShape>> cellShapes; // Shapes of the grid cells

	std::vector<std::pair<int, int>> selectedCells; // Vector to store selected cells

public:
	Grid(int x, int y, int size, int cellSize, const sf::Font& font);
	void generateWordGrid();
	void draw(sf::RenderWindow& window);
	void handleClick(int mouseX, int mouseY, std::string& userInput);
};

#endif // GRID_H
