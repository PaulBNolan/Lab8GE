#include "Player.h"

Player* m_player = new Player();

int main()
{

	std::thread m_updateThread = std::thread(&Player::Update,m_player);
	std::thread m_inputThread = std::thread(&Player::Input,m_player);
	std::thread m_renderThread = std::thread(&Player::Render, m_player);

	m_inputThread.join();
	m_updateThread.join();
	m_renderThread.join();

	return 0;
}