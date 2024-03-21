#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace SnakeGame
{
    enum class SnakeDirection
    {
        Down = 0,
        Left,
        Right,
        Up
    };

    struct Snake
    {
        int numTiles = 2; //נאחלונ חלוט
        SnakeDirection direction = SnakeDirection::Right;
        Position2D snakePosition[NUM_TILES_X * NUM_TILES_Y];

        //דמכמגא חלוט
        sf::Texture snakeHeadTexture;
        sf::Sprite snakeSprite;

        //עוכמ חלוט
        sf::Texture snakeBodyTexture;
        sf::Sprite snakeBodySprite;
    };

    struct Game;

    void InitSnake(Snake& snake);
    void UpdateSnake(Snake& snake, Game& game);
    void CheckCollisionWithBorder(Snake& snake, Game& game);
    void Defeat(Snake& snake, Game& game);
    void HandleInput(Snake& snake);
    void DrawSnake(Snake& snake, sf::RenderWindow& window);
}
