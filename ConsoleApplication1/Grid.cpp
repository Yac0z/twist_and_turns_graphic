#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Constructor to initialize grid properties
Grid::Grid(int x, int y, int size, int cellSize, const sf::Font& font)
	: gridX(x), gridY(y), gridSize(size), cellSize(cellSize), font(font) {
	// Initialize the grid and cells
	generateWordGrid();
	// Initialize selectedCells with a default pair {-1, -1} to indicate no selection
	selectedCells.push_back({ -1, -1 });
}

// Generate the word grid
void Grid::generateWordGrid() {
	words.resize(gridSize, std::vector<std::string>(gridSize, "Word"));
	cellShapes.resize(gridSize, std::vector<sf::RectangleShape>(gridSize));

	for (int row = 0; row < gridSize; ++row) {
		for (int col = 0; col < gridSize; ++col) {
			sf::RectangleShape& cell = cellShapes[row][col];
			cell.setSize(sf::Vector2f(cellSize, cellSize));
			cell.setPosition(gridX + col * cellSize, gridY + row * cellSize);
			cell.setFillColor(sf::Color::White);  // Initially, all cells are white
			cell.setOutlineColor(sf::Color::Black);
			cell.setOutlineThickness(1.0f);
		}
	}
}

// Draw the grid on the window
void Grid::draw(sf::RenderWindow& window) {
	for (int row = 0; row < gridSize; ++row) {
		for (int col = 0; col < gridSize; ++col) {
			window.draw(cellShapes[row][col]);
		}
	}
}

// Handles click events for cell selection
void Grid::handleClick(int mouseX, int mouseY, std::string& userInput) {
	int row = (mouseY - gridY) / cellSize;
	int col = (mouseX - gridX) / cellSize;

	// Check if the click is within bounds
	if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
		sf::RectangleShape& cell = cellShapes[row][col];

		// Check if it's a valid selection (based on being a neighbor)
		if (cell.getFillColor() == sf::Color::White) {
			// Get the last selected cell (the last element of the vector)
			auto lastSelected = selectedCells.back();

			// If the last selected cell is {-1, -1}, it means no cell has been selected yet
			bool isNeighbor = (lastSelected.first == -1 && lastSelected.second == -1) ||
				(std::abs(row - lastSelected.first) <= 1 && std::abs(col - lastSelected.second) <= 1);

			// If it's a valid neighbor or it's the first selection, select it
			if (isNeighbor) {
				selectedCells.push_back({ row, col });  // Add the cell to the selectedCells vector
				cell.setFillColor(sf::Color::Yellow);
				userInput += words[row][col] + " ";
			}
		}
		// If the cell is already selected (yellow), deselect it
		else if (cell.getFillColor() == sf::Color::Yellow) {
			// Get the last selected cell (the last element of the vector)
			auto lastSelected = selectedCells.back();

			// Only deselect if the clicked cell matches the last selected one
			if (lastSelected.first == row && lastSelected.second == col) {
				// Remove the last selected cell from the selectedCells vector
				selectedCells.pop_back();
				cell.setFillColor(sf::Color::White);

				// Remove the word from userInput
				std::string wordToRemove = words[row][col] + " ";
				size_t pos = userInput.find(wordToRemove);
				if (pos != std::string::npos) {
					userInput.erase(pos, wordToRemove.length());
				}
			}
		}
	}
}
