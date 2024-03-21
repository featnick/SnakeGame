#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	struct Records
	{
		std::string name;
		int record = 0;
	};

	struct UI
	{
		sf::Font font;
		sf::Font font2;
		
		std::vector<Records> records;
		std::string recordTableString;
		sf::Text recordTable;

		std::string playerName = "XYZ";
		std::string inputText = playerName; // строка для ввода имени
		sf::Text inputtedName;

		sf::Text scoreText;
		sf::Text scoreTextGameOver;
		
		sf::Texture titleTexture;
		sf::Sprite title;

		sf::Texture pauseMenuTexture[2];
		sf::Sprite pauseMenu;

		sf::Texture mainMenuTexture[5];
		sf::Sprite mainMenu;

		sf::Texture resultMenuTexture[2];
		sf::Sprite resultMenu;

		sf::Texture levelMenuTexture[5];
		sf::Sprite levelMenu;

		sf::Texture enterNameMenuTexture[2];
		sf::Sprite enterNameMenu;
		sf::Texture nameInputMenuTexture;
		sf::Sprite nameInputMenu;

		sf::Texture settingsMenuTexture[2];
		sf::Sprite settingsMenu;
		sf::Texture checkMarkTexture;
		sf::Sprite checkMark[2];

		sf::Texture recordMenuTexture;
		sf::Sprite recordMenu;

		sf::Texture tileTexture;
		sf::Sprite tiles;

		sf::Texture borderTexture;
		sf::Sprite border;

		int menuItem = 0; //итератор по пунктам меню
		float timer = 0; //таймер для меню (чтобы после перехода в другое меню не прожимался сразу 1 из пунктов)
		bool nameEntered = false; //введено ли имя игроком
	};

	struct Game;
	enum class GameState;

	static void InitText(sf::Text& text, sf::Font& font, sf::Color color, sf::String string, int size, float positionX, float positionY);
	void InitMenu(sf::Texture texture[], sf::Sprite& sprite, std::string fileName, float posX, float posY, 
		float originX, float originY, float scaleX, float scaleY, int arraySize);
	void InitSprite(sf::Texture& texture, sf::Sprite& sprite, std::string fileName, float posX, float posY, float originX, float originY, float scaleX, float scaleY);
	void InitUI(UI& ui);
	void MenuManager(sf::Event event, Game& game, UI& ui, sf::Texture menuTexture[], sf::Sprite& menu, int size,
		GameState state1, GameState state2, GameState state3, GameState state4, GameState state5);
	void ScrollingMenu(sf::Event event, Game& game, UI& ui, sf::Texture menuTexture[], sf::Sprite& menu, int size);
	void UpdateUI(UI& ui, const Game& game);
	void SortRecordsArray(UI& ui);
	void DrawRecordTable(UI& ui, int size, sf::RenderWindow& window, int textSize, float scaleX, float scaleY, float posX, float posY, std::string n);
	void DrawTiles(UI& ui, sf::RenderWindow& window);
	void DrawUI(UI& ui, sf::RenderWindow& window, Game& game);
}