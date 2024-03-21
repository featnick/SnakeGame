#include "Sound.h"
#include "Constants.h"	
#include "assert.h"
#include "Game.h"

namespace SnakeGame
{
	void InitSound(sf::SoundBuffer& buffer, sf::Sound& sound, std::string filename, float volume)
	{
		assert(buffer.loadFromFile(RESOURCES_PATH + filename));
		sound.setBuffer(buffer);
		sound.setVolume(volume);
	}
	
	void InitSounds(Sound& sound)
	{
		// Музыкальное сопровождение в сессии
		assert(sound.music.openFromFile(RESOURCES_PATH + "music.wav"));
		sound.music.setLoop(true);
		sound.music.setVolume(20.f);
		sound.music.play();
		
		// Звук столкновения
		InitSound(sound.hitBuffer, sound.hit, "hit.wav", 30.f);

		// Звук окончания сессии
		InitSound(sound.endBuffer, sound.end, "lose.wav", 20.f);

		// Звук нажатия на кнопки
		InitSound(sound.clickBuffer, sound.click, "click.wav", 20.f);
	}

	void PlaySound(sf::Sound& sound, Game& game)
	{
		if (SettingActive(game, GameSettings::SoundOn))
		{
			sound.play();
		}
	}

	void UpdateMusic(Sound& sound, Game& game)
	{
		if (SettingActive(game, GameSettings::MusicOn)) //если параметр включен
		{
			sound.music.play(); //запускаем музыку
		}
		else
		{
			sound.music.stop();
		}	
	}
}