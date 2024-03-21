#include "Math.h"
#include <cstdlib>

namespace SnakeGame
{
	int GetRandomInt(int minInt, int maxInt)
	{
		int result;
		result = minInt + rand() % (maxInt - minInt + 1);
		return result;
	}
}