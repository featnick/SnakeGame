#include "Snake.h"
#include <assert.h>
#include "Game.h"

namespace SnakeGame
{
    void InitSnake(Snake& snake)
    {
        // ������ ������
        assert(snake.snakeHeadTexture.loadFromFile(RESOURCES_PATH + "head.png"));
        snake.snakeSprite.setTexture(snake.snakeHeadTexture);
        snake.snakeSprite.setOrigin(12.5f, 12.5f);

        // ���� ������
        assert(snake.snakeBodyTexture.loadFromFile(RESOURCES_PATH + "body.png"));
        snake.snakeBodySprite.setTexture(snake.snakeBodyTexture);

        // ��������� ��������� ������ (�����������, ���-�� ���������� ������, �������)
        snake.direction = SnakeDirection::Right;
        snake.numTiles = 2;
        for (int i = 0; i < snake.numTiles; ++i)
        {
            snake.snakePosition[i] = { 1,3 };
        }
    }

    void UpdateSnake(Snake& snake, Game& game)
	{
        // ����������� ������� ������
        for (int i = snake.numTiles; i > 0; --i) 
        {
            snake.snakePosition[i] = snake.snakePosition[i - 1];
        }

        // �������� ������ ������
        if (snake.direction == SnakeDirection::Down)
        {
            snake.snakePosition[0].y += 1; //����
        }
        if (snake.direction == SnakeDirection::Left)
        {
            snake.snakePosition[0].x -= 1; //�����
        }
        if (snake.direction == SnakeDirection::Right)
        {
            snake.snakePosition[0].x += 1; //�����
        }
        if (snake.direction == SnakeDirection::Up)
        {
            snake.snakePosition[0].y -= 1; //�����
        }

        // ���� ������ ������� ������
        if ((snake.snakePosition[0].x == game.apple.applePosition.x) && (snake.snakePosition[0].y == game.apple.applePosition.y))
        {
            snake.numTiles++; // ���������� ������
            
            game.numPoints += game.point; // ���������� �����

            RegenerateApple(game.apple, game);

            PlaySound(game.sound.hit, game);
        }

        // ��������� �� ������������ ������ � �����
        for (int i = 1; i < snake.numTiles; ++i) // ���� for ��� ���� ������ ������
        {
            if ((snake.snakePosition[0].x == snake.snakePosition[i].x) && (snake.snakePosition[0].y == snake.snakePosition[i].y))
            {
                //game.gameState = GameState::GameOver;
                Defeat(snake, game);
            }
        }

        
	}

    void CheckCollisionWithBorder(Snake& snake, Game& game)
    {
        // ��������� �� ������������ � ��������� ����
        if (snake.snakePosition[0].y == 3 && snake.direction == SnakeDirection::Up
            || snake.snakePosition[0].y == SCREEN_HEIGHT - 2 && snake.direction == SnakeDirection::Down
            || snake.snakePosition[0].x == 1 && snake.direction == SnakeDirection::Left
            || snake.snakePosition[0].x == SCREEN_WIDTH - 2 && snake.direction == SnakeDirection::Right)
        {
            Defeat(snake, game);
        }
    }

    void Defeat(Snake& snake, Game& game)
    {
        PlaySound(game.sound.hit, game);
        PlaySound(game.sound.end, game);
        game.gameState = GameState::GameOver;
        game.ui.records[NUM_RECORDS - 1].record = game.numPoints;
        SortRecordsArray(game.ui);
    }

    void HandleInput(Snake& snake)
    {
        // ���������� ������� � ������� �������
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (snake.snakePosition[0].y != snake.snakePosition[1].y)
                snake.direction = SnakeDirection::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (snake.snakePosition[0].y != snake.snakePosition[1].y)
                snake.direction = SnakeDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (snake.snakePosition[0].x != snake.snakePosition[1].x)
                snake.direction = SnakeDirection::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (snake.snakePosition[0].x != snake.snakePosition[1].x)
                snake.direction = SnakeDirection::Down;
        }
    }

    void DrawSnake(Snake& snake, sf::RenderWindow& window)
    {
        for (int i = 0; i < snake.numTiles; ++i)
        {
            if (i != 0) //������ ���� ������
            {
                snake.snakeBodySprite.setPosition(snake.snakePosition[i].x * TILE_SIZE, snake.snakePosition[i].y * TILE_SIZE);
                window.draw(snake.snakeBodySprite);
            }
        }
        snake.snakeSprite.setPosition(snake.snakePosition[0].x * TILE_SIZE + TILE_SIZE / 2.f, snake.snakePosition[0].y * TILE_SIZE + TILE_SIZE / 2.f); //����� �������
        window.draw(snake.snakeSprite); //������ ������ ������
        
        // ������ ����������� ������� ������ ������
        switch (snake.direction)
        {
        case SnakeDirection::Right:
        {
            snake.snakeSprite.setRotation(0);
            break;
        }
        case SnakeDirection::Up:
        {
            snake.snakeSprite.setRotation(-90);
            break;
        }
        case SnakeDirection::Left:
        {
            snake.snakeSprite.setRotation(180);
            break;
        }
        case SnakeDirection::Down:
        {
            snake.snakeSprite.setRotation(90);
            break;
        }
        }
    }
}
