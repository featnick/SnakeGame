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

		float timer = 0.f; // ������ ��� �������� ������

		float delay = 0.03f; // ����� �� ������� ������ �������� 1 ������
		float delayPlus = 0.03f; /* �������� �� ������� ������������� delay 
									(�������������� ����������� �������� ������)
									 � ������ ����������� ������ ��������� */

		float delayBeforeStart = 1.f; // �������� ����� ������� � ����� �����

		int point = 2; // ���������� ������������ ����� �� 1 ��������� ������
		int pointPlus = 2; /* �������� �� ������� ������������� ��� - �� ����������� �����
								����������� ������ ��������� */

		int numPoints = 0; // ���� ������

		int gameSettings = 0; // ��������� ����

		GameState gameState = GameState::AverageMode; // ������� �����/��������� ����

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