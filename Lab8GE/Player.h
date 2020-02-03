#pragma once
#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <sstream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	//Player()~;

	const int n = 10;
	std::atomic_int m_number;
	std::atomic_int m_next;
	std::atomic_int m_turn[10];
	int m_numThreads;
	std::mutex m_mutex;

	std::ostringstream m_data;

	void Update();
	void Input();
	void Render();

private:
	sf::RenderWindow m_window;

	sf::RectangleShape m_player;
	sf::Vector2f m_position;
	float m_playerWidth;
	bool m_flying;

	sf::RectangleShape m_floor;
};

