#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame 
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 32, SCREEN_HEIGHT = 24; // ширина и высота экрана в плитках
	const int NUM_TILES_X = 30, NUM_TILES_Y = 20; //количество плиток в игровом поле по x и y
	const float TILE_SIZE = 25.f; //–азмер каждой плитки
	const int NUM_RECORDS = 11; // количсетво записываемых рекордов
	const int MAX_NAME_SIZE = 20; // максимальна€ длина имени игрока
}