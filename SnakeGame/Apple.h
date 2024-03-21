#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
    struct Apple
    {
        sf::Texture appleTexture;
        sf::Sprite appleSprite;
        Position2D applePosition;
    };

    struct Game;

    void InitApple(Apple& apple);
    void RegenerateApple(Apple& apple, Game& game);
    void DrawApple(Apple& apple, sf::RenderWindow& window);
}