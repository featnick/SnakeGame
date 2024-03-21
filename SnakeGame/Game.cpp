#include "Game.h"
#include "assert.h"


namespace SnakeGame
{

	void InitGame(Game& game)
	{
		SwitchSetting(game, GameSettings::SoundOn);
		SwitchSetting(game, GameSettings::MusicOn);
		InitUI(game.ui);
		InitSounds(game.sound);
	}

	void Restart(Game& game)
	{
		game.numPoints = 0;
		InitApple(game.apple);
		InitSnake(game.snake);
	}

	void CheckDifficultyLevel(Game& game)
	{
		if (game.gameState == GameState::SimpleMode || game.gameState == GameState::HeavierSimpleMode || game.gameState == GameState::AverageMode
			|| game.gameState == GameState::LighterHeavyMode || game.gameState == GameState::HeavyMode)
		{
			if (game.gameState == GameState::SimpleMode) // �������� - 1, ���� - 2
			{
				game.delay = game.delayPlus * 5; 
				game.point = game.pointPlus * 1;
			}
			else if (game.gameState == GameState::HeavierSimpleMode) // �������� - 2, ���� - 4
			{
				game.delay = game.delayPlus * 4;
				game.point = game.pointPlus * 2;
			}
			else if (game.gameState == GameState::AverageMode) // �������� - 3, ���� - 6
			{
				game.delay = game.delayPlus * 3;
				game.point = game.pointPlus * 3;
			}
			else if (game.gameState == GameState::LighterHeavyMode) // �������� - 4, ���� - 8
			{
				game.delay = game.delayPlus * 2;
				game.point = game.pointPlus * 4;
			}
			else if (game.gameState == GameState::HeavyMode) // �������� - 5, ���� - 10
			{
				game.delay = game.delayPlus * 1;
				game.point = game.pointPlus * 5;
			}

			game.gameState = GameState::ToMainMenuTransition;
		}
	}

	void UpdateGame(Game& game, float deltaTime, sf::RenderWindow& window)
	{
		// ���������� ��������� ������� ���������
		CheckDifficultyLevel(game);

		// ������� ����� ���������� � �����-���� ����
		if (game.gameState == GameState::MainMenu || game.gameState == GameState::GamePaused || game.gameState == GameState::DifficultyMenu
			|| game.gameState == GameState::GameOver || game.gameState == GameState::EnterNameMenu || game.gameState == GameState::SettingsMenu)
		{
			game.ui.timer += deltaTime;
		}

		// ������� �� ������� ������ � ������� ����
		if (game.gameState == GameState::ToMainMenuTransition)
		{
			window.setSize({ 400, 600 });
			game.gameState = GameState::MainMenu;
		}

		// ����� ��������
		if (game.gameState == GameState::SwitchSoundSetting)
		{
			SwitchSetting(game, GameSettings::SoundOn);
			game.gameState = GameState::SettingsMenu;
		}
		else if (game.gameState == GameState::SwitchMusicSetting)
		{
			SwitchSetting(game, GameSettings::MusicOn);
			UpdateMusic(game.sound, game);
			game.ui.menuItem = 1;
			game.gameState = GameState::SettingsMenu;
		}

		// ������� ���� ����� �����, ���� ��� �� ��� �� ���� �������
		if (game.gameState == GameState::GameOver && !game.ui.nameEntered)
		{
			game.gameState = GameState::EnterNameMenu;
		}
		if (game.gameState == GameState::NoEnterName)
		{
			game.ui.nameEntered = true;
			game.gameState = GameState::GameOver;
		}

		// ������� �� ��������� ������ � ��������� �������� ������ ����
		if (game.gameState == GameState::GameStart)
		{
			window.setSize({ 800, 600 });
			Restart(game);
			game.gameState = GameState::WaitingGame;
		}

		// ����������� ��������� ����� � ��������� ������� ������
		if (game.gameState == GameState::WaitingGame)
		{
			game.timer += deltaTime;
			if (game.timer > game.delayBeforeStart)
			{
				game.timer = 0;
				game.gameState = GameState::GameActive;
			}
		}

		// ���� ������� ������ ������� - ��������� ��������� ������
		if (game.gameState == GameState::GameActive)
		{
			game.timer += deltaTime;
			if (game.timer > game.delay)
			{
				game.timer = 0.f;
				// ��������� �� ������������ ������ �� �������
				CheckCollisionWithBorder(game.snake, game);
				// ����� ��� ��� ��������� ������� ������ �� ����������
				// ����� � ������ ������������ �� ������ ������ �� ���������� ��������� � �����
				if (game.gameState == GameState::GameActive)
					UpdateSnake(game.snake, game);
			}
			HandleInput(game.snake);
		}
		UpdateUI(game.ui, game);

	}

	void CheckEvents(Game& game, sf::RenderWindow& window, float deltaTime)
	{
		while (window.pollEvent(game.event))
		{
			//��������� ����
			if (game.event.type == sf::Event::Closed || game.gameState == GameState::ExitGame)
			{
				window.close();
				break;
			}

			if (game.gameState == GameState::EnterName)
			{
				if (game.event.type == sf::Event::TextEntered)
				{
					if (game.event.text.unicode < 128) // �������� �� ASCII �������
					{
						if (game.event.text.unicode == '\b' && !game.ui.inputText.empty()) // �������� ������� ��� ������� Backspace
						{
							game.ui.inputText.pop_back();
						}
						else if (game.ui.inputText.size() < MAX_NAME_SIZE) // ���� ��������
						{
							game.ui.inputText += static_cast<char>(game.event.text.unicode);
						}
					}
				}
				// ������ ��� ������ �� ��������� �� ��� ������� �������
				if ((game.event.type == sf::Event::KeyPressed) && (game.event.key.code == sf::Keyboard::Enter))
				{
					game.ui.nameEntered = true;
					game.ui.playerName = game.ui.inputText;
					for (int i = 0; i < game.ui.records.size(); ++i)
					{
						game.ui.records[i].name = game.ui.playerName;
					}
					game.gameState = GameState::GameOver;
				}
			}

			//������ ���� �� �����
			else if ((game.event.type == sf::Event::KeyPressed) && (game.event.key.code == sf::Keyboard::P) && (game.gameState == GameState::GameActive 
				|| game.gameState == GameState::WaitingGame))
			{
				game.gameState = GameState::GamePaused;
			}

			//��������������� c ���� �����, ���� ��� �������
			else if (game.gameState == GameState::GamePaused)
			{
				MenuManager(game.event, game, game.ui, game.ui.pauseMenuTexture, game.ui.pauseMenu, (int)std::size(game.ui.pauseMenuTexture),
					GameState::WaitingGame, GameState::ToMainMenuTransition, GameState::GamePaused, GameState::GamePaused, GameState::GamePaused);
			}

			//��������������� � ������� ����, ���� ��� �������
			else if (game.gameState == GameState::MainMenu)
			{
				MenuManager(game.event, game, game.ui, game.ui.mainMenuTexture, game.ui.mainMenu, (int)std::size(game.ui.mainMenuTexture),
					GameState::GameStart, GameState::DifficultyMenu, GameState::RecordMenu, GameState::SettingsMenu, GameState::ExitGame);
			}

			//��������������� c ���� ���������� ����� ���������� ����, ���� ��� �������
			else if (game.gameState == GameState::GameOver)
			{
				MenuManager(game.event, game, game.ui, game.ui.resultMenuTexture, game.ui.resultMenu, (int)std::size(game.ui.resultMenuTexture),
					GameState::GameStart, GameState::ToMainMenuTransition, GameState::GameOver, GameState::GameOver, GameState::GameOver);
			}

			//��������������� c ���� ������ ������ ���������, ���� ��� �������
			else if (game.gameState == GameState::DifficultyMenu)
			{
				MenuManager(game.event, game, game.ui, game.ui.levelMenuTexture, game.ui.levelMenu, (int)std::size(game.ui.levelMenuTexture),
					GameState::SimpleMode, GameState::HeavierSimpleMode, GameState::AverageMode, GameState::LighterHeavyMode, GameState::HeavyMode);
			}

			//��������������� c ���� ����� �����, ���� ��� �������
			else if (game.gameState == GameState::EnterNameMenu)
			{
				MenuManager(game.event, game, game.ui, game.ui.enterNameMenuTexture, game.ui.enterNameMenu, (int)std::size(game.ui.enterNameMenuTexture),
					GameState::NoEnterName, GameState::EnterName, GameState::EnterNameMenu, GameState::EnterNameMenu, GameState::EnterNameMenu);
			}

			//��������������� c ���� ��������, ���� ��� �������
			else if (game.gameState == GameState::SettingsMenu)
			{
				MenuManager(game.event, game, game.ui, game.ui.settingsMenuTexture, game.ui.settingsMenu, (int)std::size(game.ui.settingsMenuTexture),
					GameState::SwitchSoundSetting, GameState::SwitchMusicSetting, GameState::SettingsMenu, GameState::SettingsMenu, GameState::SettingsMenu);
			}

			// ������������ � ������� ���� �� ������ ����
			if (game.gameState == GameState::DifficultyMenu || game.gameState == GameState::RecordMenu || game.gameState == GameState::SettingsMenu)
			{
				if ((game.event.type == sf::Event::KeyPressed) && (game.event.key.code == sf::Keyboard::B))
				{
					game.gameState = GameState::MainMenu;
					game.ui.menuItem = 0;
				}
			}
		}
	}


	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameState == GameState::GameActive || game.gameState == GameState::GameOver || game.gameState == GameState::GamePaused
			|| game.gameState == GameState::WaitingGame || game.gameState == GameState::EnterNameMenu || game.gameState == GameState::EnterName)
		{
			DrawTiles(game.ui, window);
			DrawApple(game.apple, window);
			DrawSnake(game.snake, window);
		}
		
		DrawUI(game.ui, window, game);
	}

	void SwitchSetting(Game& game, GameSettings setting)
	{
		game.gameSettings ^= setting;
	}

	bool SettingActive(Game& game, GameSettings setting)
	{
		return (game.gameSettings & setting) == setting;
	}
}