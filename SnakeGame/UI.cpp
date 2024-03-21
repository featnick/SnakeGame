#include "UI.h"
#include "Constants.h"
#include "assert.h"
#include "Game.h"

namespace SnakeGame
{
	static void InitText(sf::Text& text, sf::Font& font, sf::Color color, sf::String string, int size, float positionX, float positionY)
	{
		text.setCharacterSize(size);
		text.setFont(font);
		text.setFillColor(color);
		text.setPosition(positionX, positionY);
		text.setString(string);
	}

	void InitMenu(sf::Texture texture[], sf::Sprite& sprite, std::string fileName, float posX, float posY, 
		float originX, float originY, float scaleX, float scaleY, int arraySize)
	{
		for (int i = 0; i < arraySize; ++i)
		{
			assert(texture[i].loadFromFile(RESOURCES_PATH + fileName + std::to_string(i + 1) + ".png"));
		}
		sprite.setTexture(texture[0]);
		sprite.setOrigin(originX, originY);
		sprite.setPosition(posX, posY);
		sprite.setScale(scaleX, scaleY);
	}

	void InitSprite(sf::Texture& texture, sf::Sprite& sprite, std::string fileName, float posX, float posY,
		float originX, float originY, float scaleX, float scaleY)
	{
		assert(texture.loadFromFile(RESOURCES_PATH + fileName));
		sprite.setTexture(texture);
		sprite.setOrigin(originX, originY);
		sprite.setScale(scaleX, scaleY);
		sprite.setPosition(posX, posY);
	}

	void InitUI(UI& ui)
	{
		// �������� �������
		assert(ui.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Black.ttf"));
		assert(ui.font2.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		// ������������� ������� ��������
		ui.records.resize(NUM_RECORDS);
		for (int i = 0; i < ui.records.size(); ++i)
		{
			ui.records[i] = { ui.playerName, 0};
		}
		// ������������� ������ ���������� �����
		InitText(ui.inputtedName, ui.font, sf::Color::Black, ui.playerName, 20, TILE_SIZE * 15, (float)SCREEN_HEIGHT * TILE_SIZE / 2.f);

		// ������������� ������ ���-�� �����
		InitText(ui.scoreText, ui.font, sf::Color::Black, "SCORE: 0", 20, 630, 12.5);

		// ������������� ������ ���-�� ����� ����� ��������� ����
		InitText(ui.scoreTextGameOver, ui.font2, sf::Color::Black, "", 20, (float)SCREEN_WIDTH * TILE_SIZE / 2.f, TILE_SIZE * 6 + 10);
		ui.scoreTextGameOver.setOrigin(15, 0);

		// ������������� ��������� �������� ����
		InitSprite(ui.titleTexture, ui.title, "title.png", 0, 0, 0, 0, 1, 1);

		// ������������� ���� �����
		InitMenu(ui.pauseMenuTexture, ui.pauseMenu, "Menu/pauseMenu", (float)SCREEN_WIDTH * TILE_SIZE / 2.f, (float)SCREEN_HEIGHT * TILE_SIZE / 2.f,
			400.f / 2.f, 235.f / 2.f, 1, 1, (int)std::size(ui.pauseMenuTexture));

		//������������� �������� ����
		InitMenu(ui.mainMenuTexture, ui.mainMenu, "Menu/MainMenu", 0, 0,
			0, 0, 2, 1, (int)std::size(ui.mainMenuTexture));

		// ������������� ���� �����������
		InitMenu(ui.resultMenuTexture, ui.resultMenu, "Menu/ResultMenu", (float)SCREEN_WIDTH * TILE_SIZE / 2.f, (float)SCREEN_HEIGHT * TILE_SIZE / 2.f,
			400.f / 2.f, 450.f / 2.f, 1, 1, (int)std::size(ui.resultMenuTexture));

		// ������������� ���� ������ ������ ���������
		InitMenu(ui.levelMenuTexture, ui.levelMenu, "Menu/LevelMenu", 0, 0,
			0, 0, 2, 1, (int)std::size(ui.levelMenuTexture));

		// ������������� ���� ����� �����
		InitMenu(ui.enterNameMenuTexture, ui.enterNameMenu, "Menu/EnterNameMenu", (float)SCREEN_WIDTH * TILE_SIZE / 2.f, (float)SCREEN_HEIGHT * TILE_SIZE / 2.f, 
			400.f / 2.f, 271.f / 2.f, 1, 1, (int)std::size(ui.enterNameMenuTexture));
		InitSprite(ui.nameInputMenuTexture, ui.nameInputMenu, "Menu/NameInputMenu.png", (float)SCREEN_WIDTH * TILE_SIZE / 2.f, (float)SCREEN_HEIGHT * TILE_SIZE / 2.f, 
			400.f / 2.f, 271.f / 2.f, 1, 1);

		// ������������� ���� ��������
		InitMenu(ui.settingsMenuTexture, ui.settingsMenu, "Menu/SettingsMenu", 0, 0,
			0, 0, 2, 1, (int)std::size(ui.settingsMenuTexture));
		InitSprite(ui.checkMarkTexture, ui.checkMark[0], "Menu/checkMark.png", 515, 168, 0, 0, 2, 1);
		InitSprite(ui.checkMarkTexture, ui.checkMark[1], "Menu/checkMark.png", 515, 221, 0, 0, 2, 1);

		// ������������� ���� ��������
		InitSprite(ui.recordMenuTexture, ui.recordMenu, "Menu/RecordMenu.png", 0, 0, 0, 0, 2, 1);

		// ������������� ������� ������ �������� ����
		InitSprite(ui.tileTexture, ui.tiles, "tile.png", 0, 0, 0, 0, 1, 1);
		
		// ������������� ������� ������� �������� ����
		InitSprite(ui.borderTexture, ui.border, "border.png", 0, 0, 0, 0, 1, 1);
	}


	void ScrollingMenu(sf::Event event, Game& game, UI& ui, sf::Texture menuTexture[], sf::Sprite& menu, int size)
	{

		// ������������� ������ � ����
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
		{
			if (ui.menuItem == size - 1)
			{
				ui.menuItem = 0;
			}
			else
			{
				ui.menuItem += 1;
			}
		}
		else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
		{
			if (ui.menuItem == 0)
			{
				ui.menuItem = size - 1;
			}
			else
			{
				ui.menuItem -= 1;
			}
		}

		// ������ ������� ���������� ������
		menu.setTexture(menuTexture[ui.menuItem]);
	}

	void MenuManager(sf::Event event, Game& game, UI& ui, sf::Texture menuTexture[], sf::Sprite& menu, int size,
		GameState state1, GameState state2, GameState state3, GameState state4, GameState state5)
	{
		// ������������� ������ � ����
		ScrollingMenu(event, game, ui, menuTexture, menu, size);

		// ������������ ��������� ������ ����� ������� Enter
		if (ui.timer > 0.01f) // � ��������� ���������, ����� ����� �������� � ������ ���� �� ��������� ��������
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
			{
				if (ui.menuItem == 0)
				{
					game.gameState = state1;
				}
				else if (ui.menuItem == 1)
				{
					game.gameState = state2;
				}
				else if (ui.menuItem == 2)
				{
					game.gameState = state3;
				}
				else if (ui.menuItem == 3)
				{
					game.gameState = state4;
				}
				else if (ui.menuItem == 4)
				{
					game.gameState = state5;
				}

				// �������� �������� �� ������� ����
				ui.menuItem = 0;

				// �������� ������
				ui.timer = 0;
			}
	}

	void UpdateUI(UI& ui, const struct Game& game)
	{
		ui.scoreText.setString("SCORE: " + std::to_string(game.numPoints)); //����� ���-�� �����
		ui.scoreTextGameOver.setString(std::to_string(game.numPoints));

		if (game.gameState == GameState::EnterName)
		{
			ui.inputtedName.setString(ui.inputText);
		}
	}

	void SortRecordsArray(UI& ui)
	{
		//sort
		for (int i = 0; i < NUM_RECORDS; ++i)
		{
			for (int j = NUM_RECORDS - 1; j > 0; --j)
			{
				if (ui.records[j].record > ui.records[j - 1].record)
				{
					Records temp = ui.records[j];

					ui.records[j] = ui.records[j - 1];

					ui.records[j - 1] = temp;
				}
			}
		}
	}

	void DrawRecordTable(UI& ui, int size, sf::RenderWindow& window, int textSize, float scaleX, float scaleY, float posX, float posY, std::string n)
	{
		ui.recordTableString = "";
		for (int i = 0; i < size; ++i) // ���������� ������ �������� � ������
		{
			ui.recordTableString += std::to_string(i + 1) + ". " + ui.records[i].name + " - " + std::to_string(ui.records[i].record) + "\n" + n;
		}
		InitText(ui.recordTable, ui.font2, sf::Color::Black, "", textSize, posX, posY);
		ui.recordTable.setScale(scaleX, scaleY);
		ui.recordTable.setString(ui.recordTableString); // ������������� ��� ������ � sf::Text
		window.draw(ui.recordTable); // ������ �����
	}
	
	

	void DrawTiles(UI& ui, sf::RenderWindow& window)
	{
		//��� ���������� �������� ����
		for (int x = 1; x <= NUM_TILES_X; ++x)
		{
			for (int y = 3; y <= NUM_TILES_Y + 2; ++y)
			{
				ui.tiles.setPosition(x * TILE_SIZE, y * TILE_SIZE); //�������
				window.draw(ui.tiles); //������
			}
		}

		//���������� ������ ����
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			for (int y = 2; y < SCREEN_HEIGHT; ++y)
			{
				if (y == 2 || y == SCREEN_HEIGHT - 1 || x == 0 || x == SCREEN_WIDTH - 1)
				{
					ui.border.setPosition(x * TILE_SIZE, y * TILE_SIZE); // �������
					window.draw(ui.border); // ������
				}
			}
		}
	}

	void DrawUI(UI& ui, sf::RenderWindow& window, Game& game)
	{
		if (game.gameState == GameState::MainMenu)
		{
			window.draw(ui.mainMenu); // ������ ������� ����
		}
		else if (game.gameState == GameState::DifficultyMenu)
		{
			window.draw(ui.levelMenu); // ������ ���� ������ ������ ���������
		}
		else if (game.gameState == GameState::RecordMenu)
		{
			window.draw(ui.recordMenu); // ������ ���� ��������
			DrawRecordTable(ui, 10, window, 20, 2, 1, TILE_SIZE * 6, TILE_SIZE * 4, "\n"); // ������� ������� ��������
		}
		else if (game.gameState == GameState::SettingsMenu)
		{
			window.draw(ui.settingsMenu); // ������ ���� ��������
			if (SettingActive(game, GameSettings::SoundOn)) //������ ������� ���� �������� �������
			{
				window.draw(ui.checkMark[0]); 
			}
			if (SettingActive(game, GameSettings::MusicOn)) //������ ������� ���� �������� �������
			{
				window.draw(ui.checkMark[1]);
			}
		}
		else
		{
			window.draw(ui.title); // ������ ���������
			window.draw(ui.scoreText); // � ����
			if (game.gameState == GameState::GamePaused)
			{
				window.draw(ui.pauseMenu); // ������ ���� �����
			}
			else if (game.gameState == GameState::EnterNameMenu)
			{
				window.draw(ui.enterNameMenu); // ������ ����
			}
			else if (game.gameState == GameState::EnterName)
			{
				window.draw(ui.nameInputMenu); // ������ ����
				window.draw(ui.inputtedName); // ������ ��������� ���
			}
			else if (game.gameState == GameState::GameOver)
			{
				window.draw(ui.resultMenu); // ������ ���� ���������� ����
				window.draw(ui.scoreTextGameOver); // ������� �������� ���� 
				DrawRecordTable(ui, 5, window, 17, 1, 1, TILE_SIZE * 14, TILE_SIZE * 9, ""); // ������� ������� ��������
			}
			
		}

	}
}
