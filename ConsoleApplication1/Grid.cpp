#include "Grid.h"
#include <cstdlib>
#include <ctime>


// Constructor
Grid::Grid(int x, int y, int size, int cellSize, const sf::Font& font)
    : gridX(x), gridY(y), gridSize(size), cellSize(cellSize), font(font) {
    generateWordGrid();
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
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Black);
    cell.setFillColor(sf::Color::White);

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            // Draw cell
            cell.setPosition(gridX + j * cellSize, gridY + i * cellSize);
            window.draw(cell);

            // Draw word
            sf::Text wordText(words[i][j], font, 15);
            wordText.setFillColor(sf::Color::Black);
            wordText.setPosition(gridX + j * cellSize + 10, gridY + i * cellSize + 10);
            window.draw(wordText);
        }
    }
}

// Handles click events to retrieve a word
std::string Grid::handleClick(int mouseX, int mouseY) {
    int row = (mouseY - gridY) / cellSize;
    int col = (mouseX - gridX) / cellSize;

    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
        return words[row][col];
    }

    return ""; // Return empty string if click is outside the grid
}
