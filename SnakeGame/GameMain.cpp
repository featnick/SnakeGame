#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace SnakeGame;

int main()
{
    int seed = (int)time(nullptr);
    srand(seed);

    //Инициализация окна
    sf::RenderWindow window(sf::VideoMode((int)TILE_SIZE * SCREEN_WIDTH, (int)TILE_SIZE * SCREEN_HEIGHT), "Snake game!");

    //Инициализация игры
    Game game;
    InitGame(game);

    //Инициализация игрового времени
    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    // Основоной игровой цикл
    while (window.isOpen())
    {
        //Игровое время
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Проверка и обновление событий в окне
        CheckEvents(game, window, deltaTime);

        // Обновление игры
        UpdateGame(game, deltaTime, window);

        // Отрисовка игры
        window.clear();
        DrawGame(game, window);
        window.display();
    }

    return 0;
}