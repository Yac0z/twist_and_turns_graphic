#pragma once
#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Grid {
private:
    int gridX, gridY, gridSize, cellSize;
    std::vector<std::vector<std::string>> words; // Words in the grid
    sf::Font font;

    void generateWordGrid(); // Helper to generate random words

public:
    Grid(int x, int y, int size, int cellSize, const sf::Font& font);
    void draw(sf::RenderWindow& window);          // Draws the grid
    std::string handleClick(int mouseX, int mouseY); // Handles clicks and retrieves the word
};

#endif // GRID_HPP
