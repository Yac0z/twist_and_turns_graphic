#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

const int gridSize = 10;  // Grid dimensions
const int cellSize = 40;  // Size of each grid cell


// Function to create a button
sf::RectangleShape createButton(int x, int y, int width, int height, sf::Color color) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(color);
    return button;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Word Game");
    window.setFramerateLimit(60);

    // Fonts and text setup
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    // Create the grid object
    Grid grid(200, 50, gridSize, cellSize, font);

    // Define layout dimensions
    int leftColumnWidth = 150;
    int rightColumnWidth = 150;
    int centerColumnWidth = 800 - leftColumnWidth - rightColumnWidth;

    // Player 1 - Buttons and Score
    sf::RectangleShape hintButton1 = createButton(20, 400, 100, 50, sf::Color(150, 75, 0));
    sf::Text hintText1("Hint", font, 20);
    hintText1.setFillColor(sf::Color::White);
    hintText1.setPosition(30, 410);

    sf::RectangleShape undoButton1 = createButton(20, 470, 100, 50, sf::Color(150, 75, 0));
    sf::Text undoText1("Undo", font, 20);
    undoText1.setFillColor(sf::Color::White);
    undoText1.setPosition(30, 480);

    sf::RectangleShape dictButton1 = createButton(20, 540, 100, 50, sf::Color(150, 75, 0));
    sf::Text dictText1("Dict", font, 20);
    dictText1.setFillColor(sf::Color::White);
    dictText1.setPosition(30, 550);

    sf::Text scoreText1("Score: 0", font, 20);
    scoreText1.setFillColor(sf::Color::White);
    scoreText1.setPosition(20, 340);

    sf::Text player1Name("Player 1", font, 20);
    player1Name.setFillColor(sf::Color::White);
    player1Name.setPosition(20, 310);

    // Player 2 - Buttons and Score
    sf::RectangleShape hintButton2 = createButton(650, 400, 100, 50, sf::Color(75, 150, 0));
    sf::Text hintText2("Hint", font, 20);
    hintText2.setFillColor(sf::Color::White);
    hintText2.setPosition(660, 410);

    sf::RectangleShape undoButton2 = createButton(650, 470, 100, 50, sf::Color(75, 150, 0));
    sf::Text undoText2("Undo", font, 20);
    undoText2.setFillColor(sf::Color::White);
    undoText2.setPosition(660, 480);

    sf::RectangleShape dictButton2 = createButton(650, 540, 100, 50, sf::Color(75, 150, 0));
    sf::Text dictText2("Dict", font, 20);
    dictText2.setFillColor(sf::Color::White);
    dictText2.setPosition(660, 550);

    sf::Text scoreText2("Score: 0", font, 20);
    scoreText2.setFillColor(sf::Color::White);
    scoreText2.setPosition(650, 340);

    sf::Text player2Name("Player 2", font, 20);
    player2Name.setFillColor(sf::Color::White);
    player2Name.setPosition(650, 310);

    // Center column: Matrix and Input box
    int gridX = leftColumnWidth + 50;
    int gridY = 50;

    sf::RectangleShape inputBox(sf::Vector2f(centerColumnWidth - 100, 50));
    inputBox.setPosition(gridX, gridY + gridSize * cellSize + 20);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(1);

    sf::Text inputText("", font, 20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(gridX + 10, gridY + gridSize * cellSize + 30);

    sf::Text timerText("", font, 20);
    timerText.setFillColor(sf::Color::White);
    float timerX = gridX + (inputBox.getSize().x - timerText.getLocalBounds().width) / 2;
    timerText.setPosition(timerX, gridY + gridSize * cellSize + 80);

    std::string userInput;

    // Create a clock for tracking elapsed time
    sf::Clock gameClock;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Mouse click handling for the grid
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::string word = grid.handleClick(event.mouseButton.x, event.mouseButton.y);
                    if (!word.empty()) {
                        userInput += word + " ";
                        inputText.setString(userInput);
                    }
                }
            }
            // Text input handling
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !userInput.empty()) {
                    userInput.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                    userInput += static_cast<char>(event.text.unicode);
                }
                inputText.setString(userInput);
            }

            // Button click handling
            if (event.type == sf::Event::MouseButtonPressed) {
                if (hintButton1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Player 1 Hint button pressed!\n";
                }
                else if (undoButton1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Player 1 Undo button pressed!\n";
                }
                else if (dictButton1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Player 1 Dict button pressed!\n";
                }
                else if (hintButton2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Player 2 Hint button pressed!\n";
                }
                else if (undoButton2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Player 2 Undo button pressed!\n";
                }
                else if (dictButton2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Player 2 Dict button pressed!\n";
                }
            }
        }

        // Update timer
        sf::Time elapsed = gameClock.getElapsedTime();
        std::stringstream timerStream;
        timerStream << "Time: " << std::fixed << std::setprecision(2) << elapsed.asSeconds() << "s";
        timerText.setString(timerStream.str());

        // Center timer text
        float timerX = gridX + (inputBox.getSize().x - timerText.getLocalBounds().width) / 2;
        timerText.setPosition(timerX, gridY + gridSize * cellSize + 80);

        // Rendering
        window.clear(sf::Color(200, 150, 100));  // Background color

        // Draw Player 1
        window.draw(player1Name);
        window.draw(scoreText1);
        window.draw(hintButton1);
        window.draw(hintText1);
        window.draw(undoButton1);
        window.draw(undoText1);
        window.draw(dictButton1);
        window.draw(dictText1);

        // Draw Player 2
        window.draw(player2Name);
        window.draw(scoreText2);
        window.draw(hintButton2);
        window.draw(hintText2);
        window.draw(undoButton2);
        window.draw(undoText2);
        window.draw(dictButton2);
        window.draw(dictText2);

        // Draw center column (grid, input box, and timer)
        //drawGrid(window, gridX, gridY, gridSize, cellSize);
        grid.draw(window);
        window.draw(inputBox);
        window.draw(inputText);
        window.draw(timerText);

        window.display();
    }

    return 0;
}
