#pragma once
#include <SFML/Audio.hpp>

namespace SnakeGame
{
	struct Sound
	{
		sf::Music music;
		
		sf::SoundBuffer hitBuffer;
		sf::Sound hit;

		sf::SoundBuffer endBuffer;
		sf::Sound end;

		sf::SoundBuffer clickBuffer;
		sf::Sound click;
	};

	struct Game;

	void InitSound(sf::SoundBuffer& buffer, sf::Sound& sound, std::string filename, float volume);
	void InitSounds(Sound& sound);
	void PlaySound(sf::Sound& sound, Game& game);
	void UpdateMusic(Sound& sound, Game& game);
}