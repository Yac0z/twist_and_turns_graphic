#include "Grid.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

// Constructor
Grid::Grid(int x, int y, int size, int cellSize, const sf::Font& font)
	: gridX(x), gridY(y), gridSize(size), cellSize(cellSize), font(font) {
	generateWordGrid();

	// Initialize the grid shapes
	cellShapes.resize(gridSize, std::vector<sf::RectangleShape>(gridSize));
	for (int i = 0; i < gridSize; ++i) {
		for (int j = 0; j < gridSize; ++j) {
			sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
			cell.setOutlineThickness(1);
			cell.setOutlineColor(sf::Color::Black);
			cell.setFillColor(sf::Color::White);
			cell.setPosition(gridX + j * cellSize, gridY + i * cellSize);
			cellShapes[i][j] = cell;
		}
	}
}

// Generates random words for the grid
void Grid::generateWordGrid() {
	std::vector<std::string> wordList = { "cat", "dog", "apple", "ball", "tree", "mouse", "code", "game", "grid", "fun" };
	words.resize(gridSize, std::vector<std::string>(gridSize));

	std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random generator

	for (int i = 0; i < gridSize; ++i) {
		for (int j = 0; j < gridSize; ++j) {
			words[i][j] = wordList[std::rand() % wordList.size()];
		}
	}
}

// Draws the grid with words
void Grid::draw(sf::RenderWindow& window) {
	for (int i = 0; i < gridSize; ++i) {
		for (int j = 0; j < gridSize; ++j) {
			// Draw cell
			window.draw(cellShapes[i][j]);

			// Draw word
			sf::Text wordText(words[i][j], font, 15);
			wordText.setFillColor(sf::Color::Black);
			wordText.setPosition(cellShapes[i][j].getPosition().x + 10, cellShapes[i][j].getPosition().y + 10);
			window.draw(wordText);
		}
	}
}


void Grid::handleClick(int mouseX, int mouseY, std::string& userInput) {
	int row = (mouseY - gridY) / cellSize;
	int col = (mouseX - gridX) / cellSize;

	// Check if the click is within bounds
	if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
		sf::RectangleShape& cell = cellShapes[row][col];

		// Toggle cell selection
		if (cell.getFillColor() == sf::Color::White) {
			// If it's the first selection or a valid neighbor
			if (lastSelectedCell.first == -1 && lastSelectedCell.second == -1) {
				// First selection
				lastSelectedCell.prevFirst = lastSelectedCell.first;
				lastSelectedCell.prevSecond = lastSelectedCell.second;
				lastSelectedCell.first = row;
				lastSelectedCell.second = col;

				cell.setFillColor(sf::Color::Yellow);
				userInput += words[row][col] + " ";
			}
			else {
				// Check if the current cell is a valid neighbor
				int prevRow = lastSelectedCell.first;
				int prevCol = lastSelectedCell.second;

				if (std::abs(row - prevRow) <= 1 && std::abs(col - prevCol) <= 1) {
					// Valid neighbor
					lastSelectedCell.prevFirst = lastSelectedCell.first;
					lastSelectedCell.prevSecond = lastSelectedCell.second;
					lastSelectedCell.first = row;
					lastSelectedCell.second = col;

					cell.setFillColor(sf::Color::Yellow);
					userInput += words[row][col] + " ";
				}
			}
		}
		else if (cell.getFillColor() == sf::Color::Yellow) {
			// If the cell is already selected, deselect it
			cell.setFillColor(sf::Color::White);

			// Remove the word from userInput
			std::string wordToRemove = words[row][col] + " ";
			size_t pos = userInput.find(wordToRemove);
			if (pos != std::string::npos) {
				userInput.erase(pos, wordToRemove.length());
			}

			// Reset lastSelectedCell if this was the last selected cell
			if (row == lastSelectedCell.first && col == lastSelectedCell.second) {
				lastSelectedCell.first = lastSelectedCell.prevFirst;
				lastSelectedCell.second = lastSelectedCell.prevSecond;
			}
		}
	}
}

