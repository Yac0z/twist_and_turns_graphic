#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>
#include <random>
#include <array>

// Constructor
Grid::Grid(int x, int y, int size, int cellSize, const sf::Font& font)
	: gridX(x), gridY(y), gridSize(size), cellSize(cellSize), font(font) {
	generateWordGrid();
	selectedCells.push_back({ -1, -1 });
}

// Helper function to check if a word can be placed at a given position with a specific direction
bool Grid::canPlaceWord(const std::string& word, int row, int col, int dRow, int dCol, const std::vector<std::vector<std::string>>& grid) {
	for (size_t i = 0; i < word.length(); ++i) {
		int newRow = row + i * dRow;
		int newCol = col + i * dCol;

		if (newRow < 0 || newRow >= gridSize || newCol < 0 || newCol >= gridSize) {
			return false; // Out of bounds
		}
		if (!grid[newRow][newCol].empty() && grid[newRow][newCol] != std::string(1, word[i])) {
			return false; // Conflict with existing letter
		}
	}
	return true;
}

// Helper function to place a word in the grid
void Grid::placeWord(const std::string& word, int row, int col, int dRow, int dCol,
	std::vector<std::vector<std::string>>& grid,
	std::vector<std::pair<int, int>>& wordCoords) {
	for (size_t i = 0; i < word.length(); ++i) {
		int newRow = row + i * dRow;
		int newCol = col + i * dCol;
		grid[newRow][newCol] = std::string(1, word[i]);
		wordCoords.push_back({ newRow, newCol }); // Save the coordinates
	}

	// Store word and its coordinates for future reference
	validWordCoordinates[word] = wordCoords;
}

// Generate the word grid
void Grid::generateWordGrid() {
	validWords = { "HELLO", "WORLD", "GAME", "SFML", "GRID" };
	words.resize(gridSize, std::vector<std::string>(gridSize, ""));
	cellShapes.resize(gridSize, std::vector<sf::RectangleShape>(gridSize));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distPos(0, gridSize - 1);
	std::uniform_int_distribution<> distDir(0, 7);

	std::array<std::pair<int, int>, 8> directions = {
		std::make_pair(-1, 0), std::make_pair(1, 0),
		std::make_pair(0, -1), std::make_pair(0, 1),
		std::make_pair(-1, -1), std::make_pair(-1, 1),
		std::make_pair(1, -1), std::make_pair(1, 1)
	};

	for (const std::string& word : validWords) {
		bool placed = false;

		for (int attempts = 0; attempts < 100 && !placed; ++attempts) {
			int startRow = distPos(gen);
			int startCol = distPos(gen);
			auto [dRow, dCol] = directions[distDir(gen)];

			if (canPlaceWord(word, startRow, startCol, dRow, dCol, words)) {
				std::vector<std::pair<int, int>> wordCoords;
				placeWord(word, startRow, startCol, dRow, dCol, words, wordCoords);
				placed = true; // Word successfully placed
			}
		}

		if (!placed) {
			std::cerr << "Failed to place word: " << word << std::endl;
		}
	}

	// Fill empty cells with random letters
	std::uniform_int_distribution<> distLetter('A', 'Z');
	for (int row = 0; row < gridSize; ++row) {
		for (int col = 0; col < gridSize; ++col) {
			if (words[row][col].empty()) {
				words[row][col] = std::string(1, static_cast<char>(distLetter(gen)));
			}

			sf::RectangleShape& cell = cellShapes[row][col];
			cell.setSize(sf::Vector2f(cellSize, cellSize));
			cell.setPosition(gridX + col * cellSize, gridY + row * cellSize);
			cell.setFillColor(sf::Color::White);
			cell.setOutlineColor(sf::Color::Black);
			cell.setOutlineThickness(1.0f);
		}
	}
}


// Draw the grid
void Grid::draw(sf::RenderWindow& window) {
	for (int row = 0; row < gridSize; ++row) {
		for (int col = 0; col < gridSize; ++col) {
			window.draw(cellShapes[row][col]);

			sf::Text cellText;
			cellText.setFont(font);
			cellText.setString(words[row][col]);
			cellText.setCharacterSize(cellSize / 2);
			cellText.setFillColor(sf::Color::Black);

			float textX = cellShapes[row][col].getPosition().x + (cellSize / 2.0f);
			float textY = cellShapes[row][col].getPosition().y + (cellSize / 2.0f);

			if (cellText.getLocalBounds().width > 0) {
				textX -= cellText.getLocalBounds().width / 2.0f;
			}
			if (cellText.getLocalBounds().height > 0) {
				textY -= cellText.getLocalBounds().height / 1.5f;
			}

			cellText.setPosition(textX, textY);
			window.draw(cellText);
		}
	}
}

// Provide a hint to the user
void Grid::provideHint(std::string& userInput) {
	if (selectedCells.empty() || (selectedCells.size() == 1 && selectedCells[0] == std::make_pair(-1, -1))) {
		// No selection made yet: start with the first character of a valid word
		for (const auto& [word, coordinates] : validWordCoordinates) {
			if (word.substr(0, userInput.length()) == userInput && !coordinates.empty()) {
				// Highlight the first character of the word
				const auto& firstCharCoord = coordinates[0];
				cellShapes[firstCharCoord.first][firstCharCoord.second].setFillColor(sf::Color::Yellow);
				selectedCells.push_back(firstCharCoord);
				userInput += words[firstCharCoord.first][firstCharCoord.second]; // Add to userInput
				return; // Hint provided, exit function
			}
		}
	}
	else {
		// Check if the current selection matches a valid word substring
		for (const auto& [word, coordinates] : validWordCoordinates) {
			if (word.substr(0, userInput.length()) == userInput) {
				if (userInput.length() < word.length()) {
					// Get the coordinates of the next character
					const auto& nextCharCoord = coordinates[userInput.length()];
					if (std::find(selectedCells.begin(), selectedCells.end(), nextCharCoord) == selectedCells.end()) {
						// Highlight the next character and add it to selectedCells
						cellShapes[nextCharCoord.first][nextCharCoord.second].setFillColor(sf::Color::Yellow);
						selectedCells.push_back(nextCharCoord);
						userInput += words[nextCharCoord.first][nextCharCoord.second]; // Add to userInput
						return; // Hint provided, exit function
					}
				}
			}
		}
	}

	// No hint could be provided (either invalid substring or no match found)
}


bool Grid::validateWord(const std::string& word) {
	std::cout << "Validating word: " << word << std::endl;
	std::cout << "Selected Cells: ";
	for (const auto& cell : selectedCells) {
		std::cout << "(" << cell.first << "," << cell.second << ") ";
	}
	std::cout << std::endl;

	// Check if the word is valid
	if (std::find(validWords.begin(), validWords.end(), word) != validWords.end()) {
		// Mark only the currently selected cells as green
		for (const auto& cell : selectedCells) {
			if (cell.first != -1 && cell.second != -1) {
				cellShapes[cell.first][cell.second].setFillColor(sf::Color::Green);
			}
		}

		// Remove the validated word from validWords list
		validWords.erase(std::remove(validWords.begin(), validWords.end(), word), validWords.end());

		// Remove the word's coordinates from validWordCoordinates
		auto it = validWordCoordinates.find(word);
		if (it != validWordCoordinates.end()) {
			validWordCoordinates.erase(it); // Remove the word coordinates after validation
		}

		// Clear selected cells after marking them
		selectedCells.clear();
		selectedCells.push_back({ -1, -1 });

		return true;
	}
	else {
		// If the word is invalid, reset the selected cells to white
		for (const auto& cell : selectedCells) {
			if (cell.first != -1 && cell.second != -1) {
				cellShapes[cell.first][cell.second].setFillColor(sf::Color::White);
			}
		}

		// Clear selected cells after resetting them
		selectedCells.clear();
		selectedCells.push_back({ -1, -1 });

		return false;
	}
}



// Handle click events for cell selection
void Grid::handleClick(int mouseX, int mouseY, std::string& userInput) {
	int row = (mouseY - gridY) / cellSize;
	int col = (mouseX - gridX) / cellSize;

	if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
		sf::RectangleShape& cell = cellShapes[row][col];

		if (cell.getFillColor() == sf::Color::White) {
			auto lastSelected = selectedCells.back();
			bool isNeighbor = (lastSelected.first == -1 && lastSelected.second == -1) ||
				(std::abs(row - lastSelected.first) <= 1 && std::abs(col - lastSelected.second) <= 1);

			if (isNeighbor) {
				selectedCells.push_back({ row, col });
				cell.setFillColor(sf::Color::Yellow);
				userInput += words[row][col];
			}
		}
		else if (cell.getFillColor() == sf::Color::Yellow) {
			auto lastSelected = selectedCells.back();
			if (lastSelected.first == row && lastSelected.second == col) {
				selectedCells.pop_back();
				cell.setFillColor(sf::Color::White);
				userInput.pop_back();
			}
		}
	}
}