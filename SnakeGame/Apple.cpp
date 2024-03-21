#include "Apple.h"
#include "assert.h"
#include "Constants.h"
#include "Game.h"

namespace SnakeGame
{
	void InitApple(Apple& apple)
	{
		//€блоко
		assert(apple.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		apple.appleSprite.setTexture(apple.appleTexture);

		//начальные кординаты €блока
		apple.applePosition = { 10,10 };
	}

	void RegenerateApple(Apple& apple, Game& game)
	{
		//ћен€ем координаты €блока
		apple.applePosition.x = GetRandomInt(1, NUM_TILES_X);
		apple.applePosition.y = GetRandomInt(3, NUM_TILES_Y + 2);

		//провер€ем не по€вилось ли €блоко в змейке
		//если по€вилось мен€ем координаты снова
		for (int i = 0; i < game.snake.numTiles; ++i)
		{
			if (game.snake.snakePosition[i].x == apple.applePosition.x && game.snake.snakePosition[i].y == apple.applePosition.y)
			{
				RegenerateApple(apple, game);
			}
		}
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.appleSprite.setPosition(apple.applePosition.x * TILE_SIZE, apple.applePosition.y * TILE_SIZE); //обновл€ем позицию €блока
		window.draw(apple.appleSprite); //–исуем €блоко
	}
}