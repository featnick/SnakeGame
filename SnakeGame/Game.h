#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Snake.h"
#include "Apple.h"
#include "Math.h"
#include "UI.h"
#include "Sound.h"

namespace SnakeGame
{
	enum class GameState
	{
		MainMenu = 0,
		GameActive,
		GamePaused,
		GameOver,
		ExitGame,
		DifficultyMenu,
		RecordMenu,
		SettingsMenu,
		SwitchSoundSetting,
		SwitchMusicSetting,
		GameStart,
		WaitingGame,
		EnterNameMenu,
		NoEnterName,
		EnterName,
		ToMainMenuTransition,
		SimpleMode,
		HeavierSimpleMode,
		AverageMode,
		LighterHeavyMode,
		HeavyMode
	};

	enum GameSettings
	{
		SoundOn = 1 << 0,
		MusicOn = 1 << 1
	};

	struct Game
	{
		Snake snake;
		Apple apple;
		UI ui;
		Sound sound;

		float timer = 0.f; // таймер для движения змейки

		float delay = 0.03f; // время за которое змейка проходит 1 плитку
		float delayPlus = 0.03f; /* значение на которое увеличивается delay 
									(соответственно уменьшается скорость змейки)
									 с каждым уменьшением уровня сложности */

		float delayBeforeStart = 1.f; // задержка перед сессией и после паузы

		int point = 2; // количество прибавляемых очков за 1 съеденное яблоко
		int pointPlus = 2; /* значение на которое увеличивается кол - во прибаляемых очков
								увеличением уровня сложности */

		int numPoints = 0; // счет игрока

		int gameSettings = 0; // настройки игры

		GameState gameState = GameState::AverageMode; // текущий экран/состояние игры

		sf::Event event;
	};

	void InitGame(Game& game);
	void Restart(Game& gaem);
	void UpdateGame(Game& game, float deltaTime, sf::RenderWindow& window);
	void CheckEvents(Game& game, sf::RenderWindow& window, float deltaTime);
	void CheckDifficultyLevel(Game& game);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void SwitchSetting(Game& game, GameSettings setting);
	bool SettingActive(Game& game, GameSettings setting);
}