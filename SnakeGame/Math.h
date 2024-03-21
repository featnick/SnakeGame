#pragma once

namespace SnakeGame
{
	struct Vector2D
	{
		int x, y;
	};

	typedef Vector2D Position2D;

	struct Records;

	int GetRandomInt(int minInt, int maxInt);
}